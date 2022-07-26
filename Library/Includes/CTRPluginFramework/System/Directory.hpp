#ifndef CTRPLUGINFRAMEWORK_DIRECTORY_HPP
#define CTRPLUGINFRAMEWORK_DIRECTORY_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class File;
    class Directory {
        public:
            enum OPResult {
                SUCCESS = 0,
                INVALID_PATH = -1,
                NOT_OPEN = -2,
                INVALID_ARG = -3,
                UNEXPECTED_ERROR = -4
            };

            /**
             * \brief Change the working directory
             * \param path The new path to set as working directory
             * \return An \ref OPResult code
             */
            static int ChangeWorkingDirectory(const string &path);

            /**
             * \brief Create a directory
             * \param path Path of the directory to create
             * \return Either a value from \ref OPResult or a FS return value
             */
            static int Create(const string &path);

            /**
             * \brief Remove the specified directoy
             * \param path The directory to remove
             * \return Either a value from \ref OPResult or a FS return value
             */
            static int Remove(const string &path);

            /**
             * \brief Rename the specified directory
             * \param oldPath The directory to rename
             * \param newPath The new name of the directory
             * \return Either a value from \ref OPResult or a FS return value
             */
            static int Rename(const string &oldPath, const string &newPath);

            /**
             * \brief Check if the specified directory exists
             * \param path The directory to check
             * \return 1: Exists. 0: Doesn't exists
             */
            static int IsExists(const string &path);

            /**
             * \brief Open a directory
             * \param output Reference to the Directory object
             * \param path The directory to open
             * \param create If the directory must be created
             * \return Either a value from \ref OPResult or a FS return value
             */
            static int Open(Directory &output, const string &path, bool create = false);

            /**
             * \brief Close a Directory
             * \return Either a value from \ref OPResult or a FS return value
             */
            int Close(void) const;

            /**
             * \brief Open a file within the current Directory
             * \param output The File object
             * \param path The file to open
             * \param mode The mode to open the file with
             * \return Either a value from \ref OPResult or a FS return value
             */
            int OpenFile(File &output, const string &path, int mode = File::RW) const;

            /**
             * \brief List all the files within the current Directory
             * \param files The list of files that will be returned. Beware that the container is not emptied and results files are appended
             * \param pattern If specified, only the files that contain the pattern will be returned
             * \return The count of files found, OPResult::NOT_OPEN if the Directory is not opened
             */
            int ListFiles(vector<string> &files, const string &pattern = "") const;

            /**
            * \brief List all the directories within the current Directory
            * \param directories The list of directories that will be returned. Beware that the container is not emptied and results directories are appended
            * \param pattern If specified, only the directories that contain the pattern will be returned
            * \return The count of directories found, OPResult::NOT_OPEN if the Directory is not opened
            */
            int ListDirectories(vector<string> &directories, const string &pattern = "") const;

            /**
             * \brief Get the name of the current Directory
             * \return An string with the name of the current Directory
             */
            string GetName(void) const;

            /**
             * \brief Get the full path of the current Directory
             * \return An string with the full path of the current Directory
             */
            string GetFullName(void) const;

            /**
             * \brief Check if the current Directory is open
             * \return true if the specified path was successfully opened, false otherwise
             */
            bool IsOpen(void) const;

            Directory(void);
            Directory(const string &path, bool create = false);
            ~Directory();

        private:
            int _List(void) const;
            string _path;
            Handle _handle;
            mutable bool _isOpen;
            mutable Mutex _mutex;

            struct DirectoryEntry {
                DirectoryEntry(u32 attrib, u8 *name);
                u32 attributes;
                string name;
            };

            mutable vector<DirectoryEntry> _list;
    };
}

#endif