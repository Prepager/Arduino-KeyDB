# Arduino - EEPROM Key Database
This library is a wrapper around EEPROM as a key storing database. The libraries initial purpose was to be used for RFID HEX ID storing and verification.

## Methods
``int KeyDB::count()`` _Returns key count from storage._

``void KeyDB::loadKeys()`` _Loads keys from storage into array._

``void KeyDB::saveKeys()`` _Saves array keys to storage._

``void KeyDB::addKey(String key)`` _Adds key to array and storage._

``void KeyDB::removeKey(String key)`` _Removes key from array and shift indexes._
> Because of heavy read/write actions when removing you must manually call KeyDB::saveKeys() to save changes.

``bool KeyDB::keyExists(String key)`` _Checks if key exists in array._

``String KeyDB::keyLengthen(String key)`` _Forces a key to a fixed defined length._

## Variables
``#define DB_KEY_MAX 12`` _The maximum amount of keys in the database._

``#define DB_KEY_LENGTH 8`` _The char length of the key._

``String KeyDB::keys[DB_KEY_MAX] = {""}`` _The main array of keys._

## Usage
> **BEFORE USE:** The initial count must be set by doing: ``#include <EEPROM.h>`` & ``EEPROM.write(0, 0);``
```cpp
// Include the KeyDB file.
#include "KeyDB.h"

// Create a new KeyDB object.
KeyDB database;

void setup() {
    Serial.begin(9600);

    // Add new key to database.
    database.addKey("ABC12345");

    // Check if it exists in storage.
    if (database.keyExists("ABC12345"))
        Serial.println("Valid key!");
}
```
