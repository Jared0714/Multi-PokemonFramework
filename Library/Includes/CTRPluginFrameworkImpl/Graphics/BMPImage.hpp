#ifndef CTRPLUGINFRAMEWORK_BMPIMAGE_HPP
#define CTRPLUGINFRAMEWORK_BMPIMAGE_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class BMPImage {
        struct BitmapFileHeader {
            u16 type;
            u32 size;
            u16 reserved1;
            u16 reserved2;
            u32 off_bits;

            void Clear(void);
            bool Read(File &file);
        } PACKED;

        struct BitmapInformationHeader {
            u32 size;
            u32 width;
            u32 height;
            u16 planes;
            u16 bit_count;
            u32 compression;
            u32 size_image;
            u32 x_pels_per_meter;
            u32 y_pels_per_meter;
            u32 clr_used;
            u32 clr_important;

            void Clear(void);
            bool Read(File &file);
        } PACKED;

        public:
            enum ChannelMode {
                RGB_Mode = 0,
                BGR_Mode = 1,
                RGB565_Mode = 2,
            };

            enum ColorPlane {
                BluePlane  = 0,
                GreenPlane = 1,
                RedPlane   = 2
            };

            struct Pixel {
                u8 b;
                u8 g;
                u8 r;
            } PACKED;

            BMPImage(void);
            BMPImage(void *data);
            BMPImage(const string &filename);
            BMPImage(const u32 width, const u32 height);
            BMPImage(const BMPImage &src, const u32 width, const u32 height);
            ~BMPImage();

            bool IsLoaded(void) const;
            u32 Width(void) const;
            u32 Height(void) const;
            u32 BytesPerPixel(void) const;
            const IntVector &GetDimensions(void) const;

            u8 *data(void) const;
            u8 *end(void) const;
            inline u8 *Row(u32 rowIndex) const;
            inline void DataClear(void);
            void SetWidthHeight(const u32 width, const u32 height);
            void Unload(void);
            void Draw(int x, int y);
            void Draw(const IntVector &point);
            void Draw(const IntRect &area, float fade = 0.f);
            void SaveImage(const string &filename) const;

            // Channels manipulation
            void BGRtoRGB(void);
            void RGBtoBGR(void);
            void OptimiseForRendering(void);
            void ReverseChannels(void);

            void FillWithImg(const BMPImage &src);
            bool Resample(BMPImage &dest, int newWidth, int newHeight);
            void SubSample(BMPImage &dest);
            void UpSample(BMPImage &dest);

            // Cut a part of the image into another
            bool Region(const u32 &x, const u32 &y, const u32 &width, const u32 &height, BMPImage &destImage);
            bool RoiFromCenter(const u32 cx, const u32 cy, const u32 &width, const u32 &height, BMPImage &destImage);

        private:
            // Create a new buffer according to size
            int _CreateBitmap(void);

            // Load a bmp from _filename
            void _LoadBitmap(void);
            void _LoadBitmapFromMemory(void *data);

            u8 *_data{nullptr};
            u32 _dataSize{};
            u16 _width{};
            u16 _height{};
            u16 _rowIncrement{};
            u16 _bytesPerPixel{3};
            IntVector _dimensions;

            bool _loaded{false};
            ChannelMode _channelMode{BGR_Mode};
            string _filename;
            static const u32 HeaderSize;
    };
}

#endif