#ifndef CTRPLUGINFRAMEWORK_FILE_HPP
#define CTRPLUGINFRAMEWORK_FILE_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class File {
        public:
            enum SeekPos {
                CUR,
                SET,
                END
            };

            enum Mode {
                READ = 1,
                WRITE = 1 << 1,
                CREATE = 1 << 2,
                APPEND = 1 << 3,
                TRUNCATE = 1 << 4,
                SYNC = 1 << 5,
                RW = READ | WRITE,
                RWC = READ | WRITE | CREATE
            };

            enum OPResult {
                SUCCESS = 0,
                INVALID_PATH = -1,
                NOT_OPEN = -2,
                INVALID_MODE = -3,
                INVALID_ARG = -4,
                UNEXPECTED_ERROR = -5
            };

            /**
             * \brief Create a file
             * \param path The path of the file to create
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            static int Create(const string &path);

            /**
             * \brief Rename the specified file
             * \param path Old name
             * \param newpath New name
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            static int Rename(const string &path, const string &newpath);

            /**
             * \brief Remove the specified file
             * \param path The file to remove
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            static int Remove(const string &path);

            /**
             * \brief Determines whether the specified file exists
             * \param path The file to check
             * \return 0: File doesn't exists. 1: File exists. Either a value in \ref OPResult or an error code from FS service
             */
            static int Exists(const string &path);

            /**
             * \brief Open the specified file
             * \param output File object
             * \param path The file to open
             * \param mode The mode that specifies the acces type (See \ref File::Mode)
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            static int Open(File &output, const string &path, int mode = READ | WRITE | SYNC);

            /**
             * \brief Close the file
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Close(void) const;

            /**
             * \brief Read file
             * \param buffer Where to read the data to, ensure the buffer is large enough
             * \param length Size to read in bytes
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Read(void *buffer, u32 length) const;

            /**
             * \brief Write to file
             * \param data Pointer to the data to write to the file
             * \param length Length of the data to write in bytes
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Write(const void *data, u32 length);


            /**
             * \brief Write a string to file (auto append '\n')
             * \param line Text to write
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int WriteLine(string line);

            /**
             * \brief Set the position in the file
             * \param offset Value to offset from \param origin
             * \param origin Position used as reference for \param offset
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Seek(s64 offset, SeekPos origin = CUR) const;

            /**
             * \brief Get current position in the file
             * \return The current position in file from the beginning
             */
            u64 Tell(void) const;

            /**
             * \brief Set the position to the beginning of the file
             */
            void Rewind(void) const;

            /**
             * \brief Flushes a file's content
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Flush(void) const;

            /**
             * \brief Get the size of the file
             * \return File size if >= 0. Either a value in \ref OPResult or an error code from FS service otherwise
             */
            u64 GetSize(void) const;

            void SetPriority(u32 priority);

            /**
             * \brief Write the content of the memory to the file
             * \param address Address to start reading the memory from
             * \param length Length in bytes to write to the file
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Dump(u32 address, u32 length);

            /**
             * \brief Write the content of the file (from current position) to memory
             * \param address Address to copy the content to
             * \param length Length in bytes to copy
             * \return Either a value in \ref OPResult or an error code from FS service
             */
            int Inject(u32 address, u32 length) const;

            /**
             * \brief Check if the file is open or not
             * \return True if open, false otherwise
             */
            bool IsOpen(void) const;

            /**
             * \brief Gets the full path of the file
             * \return An string with the full path of the file
             */
            string GetFullName(void) const;

            /**
             * \brief Get the file name
             * \return An string with the name of the file
             */
            string GetName(void) const;

            /**
             * \brief Get the extension of the file
             * \return An string with the extension part of the file
             */
            string GetExtension(void) const;

            File(void);
            File(const string &path, u32 mode = READ | WRITE | SYNC);
            ~File() { Close(); }

        private:
            mutable string _path;
            mutable Handle _handle;
            mutable u64 _offset;
            mutable int _mode;
            mutable bool _isOpen;
            mutable Mutex _mutex;
    };
}

#endif