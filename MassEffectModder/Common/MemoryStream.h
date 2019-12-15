/* The MIT License
 *
 * Copyright (c) 2017-2019 Pawel Kolodziejski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H

#include "Types.h"
#include "Stream.h"
#include "ByteBuffer.h"

class MemoryStream : public Stream
{
private:

    enum BufferSize
    {
        initialBufferSize = 1000,
    };

    int64_t length;
    int64_t position;
    uint8_t *internalBuffer;
    int64_t internalBufferSize;

public:

    MemoryStream();
    MemoryStream(const ByteBuffer &buffer);
    MemoryStream(const ByteBuffer &buffer, int64_t offset);
    MemoryStream(const ByteBuffer &buffer, int64_t offset, int64_t count);
    MemoryStream(QString &filename, int64_t offset, int64_t count);
    MemoryStream(QString &filename, int64_t count);
    MemoryStream(QString &filename);
    ~MemoryStream() override;

    qint64_t Length() override { return length; }
    qint64_t Position() override { return position; }

    void Flush() override {}
    void Close() override {}
    ByteBuffer ToArray();

    void CopyFrom(Stream &stream, int64_t count, int64_t bufferSize = 10000) override;
    void ReadToBuffer(uint8_t *buffer, int64_t count) override;
    ByteBuffer ReadToBuffer(int64_t count) override;
    void WriteFromBuffer(uint8_t *buffer, int64_t count) override;
    void WriteFromBuffer(const ByteBuffer &buffer) override;
    void ReadStringASCII(QString &str, int64_t count) override;
    void ReadStringASCIINull(QString &str) override;
    void ReadStringUnicode16(QString &str, int64_t count) override;
    void ReadStringUnicode16Null(QString &str) override;
    void WriteStringASCII(const QString &str) override;
    void WriteStringASCIINull(const QString &str) override;
    void WriteStringUnicode16(const QString &str) override;
    void WriteStringUnicode16Null(const QString &str) override;
    int64_t ReadInt64() override;
    uint64_t ReadUInt64() override;
    int32_t ReadInt32() override;
    uint32_t ReadUInt32() override;
    int16_t ReadInt16() override;
    uint16_t ReadUInt16() override;
    uint8_t ReadByte() override;
    void WriteInt64(int64_t value) override;
    void WriteUInt64(uint64_t value) override;
    void WriteInt32(int32_t value) override;
    void WriteUInt32(uint32_t value) override;
    void WriteInt16(int16_t value) override;
    void WriteUInt16(uint16_t value) override;
    void WriteByte(uint8_t value) override;
    void WriteZeros(int64_t count) override;
    void Seek(int64_t offset, SeekOrigin origin) override;
    void SeekBegin() override;
    void SeekEnd() override;
    void JumpTo(int64_t offset) override;
    void Skip(int64_t offset) override;
    void SkipByte() override;
    void SkipInt16() override;
    void SkipInt32() override;
    void SkipInt64() override;
};

#endif