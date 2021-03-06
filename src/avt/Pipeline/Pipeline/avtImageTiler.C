// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <avtImageTiler.h>
#include <BadIndexException.h>

#include <vtkImageData.h>

// ****************************************************************************
// Method: avtImageTiler::avtImageTiler
//
// Purpose: 
//   Constructor for the avtImageTiler class.
//
// Arguments:
//   nImg : The maximum number of images in the tiled image.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 15 17:04:01 PST 2004
//
// Modifications:
//   
// ****************************************************************************

avtImageTiler::avtImageTiler(int nImg)
{
    maxImages = nImg;
    nImages = 0;
    images = new avtImage_p[maxImages];
}

// ****************************************************************************
// Method: avtImageTiler::~avtImageTiler
//
// Purpose: 
//   Destructor for the avtImageTiler class.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 15 17:04:33 PST 2004
//
// Modifications:
//   
// ****************************************************************************

avtImageTiler::~avtImageTiler()
{
    // Delete the images in the array.
    for(int i = 0; i < maxImages; ++i)
        images[i] = 0;
    // Delete the array storage.
    delete [] images;
}

// ****************************************************************************
// Method: avtImageTiler::AddImage
//
// Purpose: 
//   Adds an image to the list of images to be added as a tile.
//
// Arguments:
//   img : A pointer to the image to be added as a tile.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 15 17:04:53 PST 2004
//
// Modifications:
//   
// ****************************************************************************

void
avtImageTiler::AddImage(avtImage_p img)
{
    if(*img == 0)
    {
        EXCEPTION0(VisItException);
    }

    if(nImages < maxImages)
    {
        images[nImages++] = img;
    }
    else
    {
        EXCEPTION2(BadIndexException,(nImages+1), maxImages);
    }
}

// ****************************************************************************
// Method: avtImageTiler::GetNumberOfColumnsForNTiles
//
// Purpose: 
//   Returns the number of columns in the tiled image for the number of tiles.
//
// Arguments:
//   nTiles : The number of tiles.
//
// Returns:    The number of columns to use.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 15 17:05:48 PST 2004
//
// Modifications:
//   
// ****************************************************************************

int
avtImageTiler::GetNumberOfColumnsForNTiles(int nTiles) const
{
    const int maxTilesPerRow[] = {1,1,2,3,2,3,3,4,4,3,4,4,4,4,4,4,4};
    int retval = 4;
    if(nTiles >= 0 && nTiles <= 16)
        retval = maxTilesPerRow[nTiles];
    return retval;
}

// ****************************************************************************
// Method: avtImageTiler::GetNumberOfRowsForNTiles
//
// Purpose: 
//   Returns the number of rows in the tiled image for the number of tiles.
//
// Arguments:
//   nTiles : The number of tiles.
//
// Returns:    The number of rows to use.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 15 17:05:48 PST 2004
//
// Modifications:
//   
// ****************************************************************************

int
avtImageTiler::GetNumberOfRowsForNTiles(int nTiles) const
{
    int nCols = GetNumberOfColumnsForNTiles(nTiles);
    int nRows = nTiles / nCols;
    if(nRows * nCols < nTiles)
        ++nRows;
    return nRows;
}

// ****************************************************************************
// Method: avtImageTiler::CreateTiledImage
//
// Purpose: 
//   Creates a tiled image and returns it.
//
// Returns:    An avtImage_p containing the new tiled image.
//
// Note:       Zbuffer and other channels on the vtkImageData's point data are
//             not currently tiled.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 15 17:06:50 PST 2004
//
// Modifications:
//   Brad Whitlock, Tue Sep 26 11:46:43 PDT 2017
//   Support tiling 4 channel images.
//
// ****************************************************************************

avtImage_p
avtImageTiler::CreateTiledImage()
{
    int tilesPerRow = GetNumberOfColumnsForNTiles(nImages);
    int nRows = GetNumberOfRowsForNTiles(nImages);

    //
    // Find the maximum size of the images so we can try to tile images with
    // different sizes.
    //
    int tileWidth = 0, tileHeight = 0;
    images[0]->GetImage().GetSize(&tileHeight, &tileWidth);
    int nColorComponents = images[0]->GetImage().GetNumberOfColorChannels();
    for(int i = 1; i < nImages; ++i)
    {
        int w, h;
        images[i]->GetImage().GetSize(&h, &w);
        tileWidth = (tileWidth < w) ? w : tileWidth;
        tileHeight = (tileHeight < h) ? h : tileHeight;
        if(images[i]->GetImage().GetNumberOfColorChannels() > nColorComponents)
            nColorComponents = images[i]->GetImage().GetNumberOfColorChannels();
    }

    //
    // Create a vtkImageData object to contain the tiled image.
    //
    int totalWidth = tileWidth * tilesPerRow;
    int totalHeight = tileHeight * nRows;
    vtkImageData *newImage = vtkImageData::New();
    newImage->SetDimensions(totalWidth, totalHeight, 1);
    newImage->AllocateScalars(VTK_UNSIGNED_CHAR, nColorComponents);
    unsigned char *output = (unsigned char *)newImage->GetScalarPointer();

    //
    // Tile the input images into the final image.
    //
    int outScanY = 0;
    int srcStart = 0;
    const unsigned char bgR = 255;
    const unsigned char bgG = 255;
    const unsigned char bgB = 255;
    const unsigned char bgA = 0;
    for(int row = 0; row < nRows; ++row)
    {
        for(int y = tileHeight-1; y >= 0; --y, ++outScanY)
        {
            unsigned char *outputRow = output + ((totalHeight-1-outScanY) *
                nColorComponents * totalWidth);
            unsigned char *p = outputRow;
            for(int s = srcStart; s < srcStart + tilesPerRow; ++s)
            {
                int x;
                if(s < nImages)
                {
                    int imgWidth = 0, imgHeight = 0;
                    images[s]->GetImage().GetSize(&imgHeight, &imgWidth);
                    vtkImageData *img = images[s]->GetImage().GetImageVTK();

                    int dY1 = (tileHeight - imgHeight) / 2;

                    if(nColorComponents == 3)
                    {
                        if(y >= dY1 && y < (dY1 + imgHeight))
                        {
                            int dX1 = (tileWidth - imgWidth) / 2;
                            int dX2 = tileWidth - imgWidth - dX1;

                            // Pad the left side of the image.
                            for(x = 0; x < dX1; ++x)
                            {
                                *p++ = bgR;
                                *p++ = bgG;
                                *p++ = bgB;
                            }

                            //
                            // Fill in the pixels.
                            //
                            if(img->GetNumberOfScalarComponents() == 4)
                            {
                                 unsigned char *srcRow = 
                                    ((unsigned char *)img->GetScalarPointer()) +
                                    ((y-dY1) * imgWidth * 4);
                                 for(x = 0; x < imgWidth; ++x)
                                 {
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     srcRow++;
                                 }
                            }
                            else if(img->GetNumberOfScalarComponents() == 3)
                            {
                                 unsigned char *srcRow = 
                                    ((unsigned char *)img->GetScalarPointer()) +
                                    ((y-dY1) * imgWidth * 3);
                                 for(x = 0; x < imgWidth; ++x)
                                 {
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                 }
                            }

                            // Pad the right side of the image.
                            for(x = 0; x < dX2; ++x)
                            {
                                *p++ = bgR;
                                *p++ = bgG;
                                *p++ = bgB;
                            }
                        }
                        else
                        {
                            // y is outside of the image so use bg color
                            for(x = 0; x < tileWidth; ++x)
                            {
                                *p++ = bgR;
                                *p++ = bgG;
                                *p++ = bgB;
                            }
                        }
                    }
                    else if(nColorComponents == 4)
                    {
                        if(y >= dY1 && y < (dY1 + imgHeight))
                        {
                            int dX1 = (tileWidth - imgWidth) / 2;
                            int dX2 = tileWidth - imgWidth - dX1;

                            // Pad the left side of the image.
                            for(x = 0; x < dX1; ++x)
                            {
                                *p++ = bgR;
                                *p++ = bgG;
                                *p++ = bgB;
                                *p++ = bgA;
                            }

                            //
                            // Fill in the pixels.
                            //
                            if(img->GetNumberOfScalarComponents() == 4)
                            {
                                 unsigned char *srcRow = 
                                    ((unsigned char *)img->GetScalarPointer()) +
                                    ((y-dY1) * imgWidth * 4);
                                 for(x = 0; x < imgWidth; ++x)
                                 {
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                 }
                            }
                            else if(img->GetNumberOfScalarComponents() == 3)
                            {
                                 unsigned char *srcRow = 
                                    ((unsigned char *)img->GetScalarPointer()) +
                                    ((y-dY1) * imgWidth * 3);
                                 for(x = 0; x < imgWidth; ++x)
                                 {
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     *p++ = *srcRow++;
                                     *p++ = 255;
                                 }
                            }

                            // Pad the right side of the image.
                            for(x = 0; x < dX2; ++x)
                            {
                                *p++ = bgR;
                                *p++ = bgG;
                                *p++ = bgB;
                                *p++ = bgA;
                            }
                        }
                        else
                        {
                            // y is outside of the image so use bg color
                            for(x = 0; x < tileWidth; ++x)
                            {
                                *p++ = bgR;
                                *p++ = bgG;
                                *p++ = bgB;
                                *p++ = bgA;
                            }
                        }
                    }
                }
                else
                {
                    // There is no input image for s. Use the background.
                    int n = tileWidth * nColorComponents;
                    for(x = 0; x < n; ++x)
                        *p++ = 0;
                }
            }
        }

        srcStart += tilesPerRow;
    }

    //
    // Now that we have a vtkImageData object, wrap it in something AVT likes.
    //
    avtImage_p retval = new avtImage(0);
    retval->GetImage() = avtImageRepresentation(newImage);
    newImage->Delete();

    return retval;
}
