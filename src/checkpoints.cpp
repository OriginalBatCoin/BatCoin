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
        (     3000, uint256("0x2e407195d4fc5571fe450e1c9ed9ce76407f547803a03dbc5410e129f12d7d15"))
        (     3427, uint256("0x9f013ec43391a52f417cbb10cdabdbec3d0091780cb2ca6be86dfee2e92eca73"))
        (     3445, uint256("0x9227548be2dc2cfde8a0c32b56c1be471011e804b3a83876c45de98a2bfed6d8"))
        (     10000, uint256("0xcd335bac144635f468c2b2fd3793e74a2f739c06dfa64aba4d60c72927b59926"))
        (     22000, uint256("0x89b8956580c34811c71e1e4a0c79b17f1577d3f93228eca84fad3dbe98313c4e"))
        (     35000, uint256("0xc2c43c740a3d98d310337e9dee77500a191d43022f78b75c30cb3536dc639189"))
        (     50000, uint256("0xd5943fca0eadf762c0857abcd8c558b002d28cf06e9cb13297c7b542be474308"))
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
