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
        (         400, uint256("0x7145983fc3f1346c95af7a3b1720c0b01c926f9379dc3ecc2a6d9c0d180f8226"))
       (         800, uint256("0x0e42f9edb41c08aff6a735f1fd33918d28ae505a6131984380729fbded363cef"))
      (     1337, uint256("0x5ea56c7f7b89da5be25ef99cc1d0b788b8936ed6e4371c2955b0d52ce5d80123"))
        (     1800, uint256("0x115b72122fcb0f7ff77cda6842b09b02951df836c7830c659fb9becf0fc874d5"))
        (     3000, uint256("0x2e407195d4fc5571fe450e1c9ed9ce76407f547803a03dbc5410e129f12d7d15"))
        (     3427, uint256("0xae6396dd949c76d386443900d012db5bb475f5f61bcc2c270e58765b4908a0f7"))
        (	  3437, uint256("0x6b10d95a9541f16c0126b22e1ba130e81f6eaf2d4d03825eb375f388f0bc0abe"))
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
