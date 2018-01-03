// Include guard.
#ifndef KEY_DB_H
#define KEY_DB_H

// Define max key count and char length.
#define DB_KEY_MAX 12
#define DB_KEY_LENGTH 8

// Include Arduino and EEPROM libraries.
#include "Arduino.h"
#include <EEPROM.h>

// Start class declaration.
class KeyDB {
    public:
        KeyDB();

        int count();
        void loadKeys();
        void saveKeys();

        void addKey(String key);
        void removeKey(String key);
        bool keyExists(String key);

        String keyLengthen(String key);
        String keys[DB_KEY_MAX] = {""};
};

#endif
