// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    
   static MapCheckpoints mapCheckpoints =
   	  boost::assign::map_list_of  //TODO: add more checkpoints
        (         0, uint256("0xa12f227d13837f1ef7a4fb5aa35922893f9bdb335907a3d070728664c13d2899"))
       (         2, uint256("0xdad976aa92fc3541e31cf541fed0dda2125e4b4adb4c8de04dad96c97229dad8"))
      (     8, uint256("0xbeb761843385c06afb3270735755bbb649ecd754c7cc4d813cd1aaa30dfe0fc2"))
        (     30, uint256("0x2ad37a5b3a89992ae485072738d7a5d4cfbe94deb5af4459ea90650d76a62b19"))
        (     41, uint256("0x5c53d4a7f1a3ad4fa7dae52648c6f994cef2f7969c6b3ee135855ee0f039d262"))
       ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
    	 return  mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

       BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
