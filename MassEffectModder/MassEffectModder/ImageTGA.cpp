/*
 * MassEffectModder
 *
 * Copyright (C) 2018 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "Image.h"

void Image::LoadImageTGA(Stream &stream)
{
    int idLength = stream.ReadByte();

    int colorMapType = stream.ReadByte();
    if (colorMapType != 0)
        CRASH_MSG("indexed TGA not supported!");

    int imageType = stream.ReadByte();
    if (imageType != 2 && imageType != 10)
        CRASH_MSG("only RGB TGA supported!");

    bool compressed = false;
    if (imageType == 10)
        compressed = true;

    stream.SkipInt16(); // color map first entry index
    stream.SkipInt16(); // color map length
    stream.Skip(1); // color map entry size
    stream.SkipInt16(); // x origin
    stream.SkipInt16(); // y origin

    int imageWidth = stream.ReadInt16();
    int imageHeight = stream.ReadInt16();
    if (!checkPowerOfTwo(imageWidth) ||
        !checkPowerOfTwo(imageHeight))
        CRASH_MSG("dimensions not power of two");

    int imageDepth = stream.ReadByte();
    if (imageDepth != 32 && imageDepth != 24)
        CRASH_MSG("only 24 and 32 bits TGA supported!");

    int imageDesc = stream.ReadByte();
    if ((imageDesc & 0x10) != 0)
        CRASH_MSG("origin right not supported in TGA!");

    bool downToTop = true;
    if ((imageDesc & 0x20) != 0)
        downToTop = false;

    stream.Skip(idLength);

    auto buffer = ByteBuffer(imageWidth * imageHeight * 4);
    quint8 *ptr = buffer.ptr();
    int pos = downToTop ? imageWidth * (imageHeight - 1) * 4 : 0;
    int delta = downToTop ? -imageWidth * 4 * 2 : 0;
    if (compressed)
    {
        int count = 0, repeat = 0, w = 0, h = 0;
        for (;;)
        {
            if (count == 0 && repeat == 0)
            {
                quint8 code = stream.ReadByte();
                if ((code & 0x80) != 0)
                    repeat = (code & 0x7F) + 1;
                else
                    count = code + 1;
            }
            else
            {
                quint8 pixelR, pixelG, pixelB, pixelA;
                if (repeat != 0)
                {
                    pixelR = stream.ReadByte();
                    pixelG = stream.ReadByte();
                    pixelB = stream.ReadByte();
                    if (imageDepth == 32)
                        pixelA = stream.ReadByte();
                    else
                        pixelA = 0xFF;
                    for (; w < imageWidth && repeat > 0; w++, repeat--)
                    {
                        ptr[pos++] = pixelR;
                        ptr[pos++] = pixelG;
                        ptr[pos++] = pixelB;
                        ptr[pos++] = pixelA;
                    }
                }
                else
                {
                    for (; w < imageWidth && count > 0; w++, count--)
                    {
                        ptr[pos++] = stream.ReadByte();
                        ptr[pos++] = stream.ReadByte();
                        ptr[pos++] = stream.ReadByte();
                        if (imageDepth == 32)
                            ptr[pos++] = stream.ReadByte();
                        else
                            ptr[pos++] = 0xFF;
                    }
                }
            }

            if (w == imageWidth)
            {
                w = 0;
                pos += delta;
                if (++h == imageHeight)
                    break;
            }
        }
    }
    else
    {
        for (int h = 0; h < imageHeight; h++, pos += delta)
        {
            for (int w = 0; w < imageWidth; w++)
            {
                ptr[pos++] = stream.ReadByte();
                ptr[pos++] = stream.ReadByte();
                ptr[pos++] = stream.ReadByte();
                if (imageDepth == 32)
                    ptr[pos++] = stream.ReadByte();
                else
                    ptr[pos++] = 0xFF;
            }
        }
    }

    pixelFormat = PixelFormat::ARGB;

    mipMaps.push_back(MipMap(buffer, imageWidth, imageHeight, PixelFormat::ARGB));

    buffer.Free();
}