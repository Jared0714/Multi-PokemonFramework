#ifndef CTRPLUGINFRAMEWORKIMPL_SEARCHBASE_HPP
#define CTRPLUGINFRAMEWORKIMPL_SEARCHBASE_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Search/Search.hpp"

namespace CTRPluginFramework {
    class Search {
        public:
            struct RegionIndex {
                u32 startIndex;
                u32 endIndex;
            };

            bool IsInProgress{true};
            bool Canceled{false};
            SearchError Error;
            u32 ResultsCount;
            float Progress;
            Time SearchTime;
            u32 Step;

            virtual void Cancel(void);
            bool ExecuteSearch(void);

            virtual void ReadResults(u32 index, vector<string> &addr, vector<string> &newVal, vector<string> &oldVal) = 0;
            const Header &GetHeader(void) const;
            u32 GetTotalResults(const Header &header) const;
            void ExtractPreviousHits(void *data, u32 index, u32 structSize, u32 &nbItem, bool forced = false);

            SearchFlags GetType(void) const;
            bool IsFirstUnknownSearch(void) const;
            virtual ~Search() {};

        protected:
            Search(Search *previous);
            Search(Search *previous, const string &filename);

            void WriteHeader(void);
            void WriteResults(void);
            virtual void UpdateProgress(void);
            virtual bool CheckNextRegion(void);
            virtual bool FirstSearchSpecified(void) = 0;
            virtual bool FirstSearchUnknown(void) = 0;
            virtual bool SecondSearchSpecified(void) = 0;
            virtual bool SecondSearchUnknown(void) = 0;
            virtual bool SubsidiarySearchSpecified(void) = 0;
            virtual bool SubsidiarySearchUnknown(void) = 0;

            void CreateIndexTable(void);
            u32 GetRegionIndex(u32 index);

            u32 _indexRegion;
            u32 _startRegion;
            u32 _endRegion;
            u32 _achievedRegionSize;
            u32 _totalRegionSize;
            u32 _currentAddress;
            u32 _maxResults;
            u32 _resultsInPool;
            u32 _resultSize;
            u32 _flags;
            Clock clock;
            File _file;
            Header _header;
            Search *_previous;
            vector<RegionIndex> _indexTable;
    };
}

#endif