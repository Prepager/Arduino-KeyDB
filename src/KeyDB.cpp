// Include header file.
#include "KeyDB.h"

/**
 * Load all keys into array on init.
 */
KeyDB::KeyDB() {
    this->loadKeys();
}

/**
 * Returns key count from storage.
 *
 * @return int
 */
int KeyDB::count() {
    return EEPROM.read(0);
}

/**
 * Loads keys from storage into array.
 */
void KeyDB::loadKeys() {
    // Read key count from storage.
    int count = this->count();
    
    // Loop through key count.
    int position = 1;
    for (int i = 0; i < count; i++) {
        // Loop through the key char length.
        for(int k = 0; k < DB_KEY_LENGTH; k++) {
            // Add read char to key string.
            char readChar = char(EEPROM.read(position));
            this->keys[i].concat(readChar);

            // Increment position.
            position++;
        }
    }
}

/**
 * Saves array keys to storage.
 */
void KeyDB::saveKeys() {
    // Loop through the key list.
    int keys = 0;
    int position = 1;
    for (int i = 0; i < DB_KEY_MAX; i++) {
        // Break out of array if empty.
        if (this->keys[i] == "")
            break;

        // Loop through the key char length.
        for(int k = 0; k < DB_KEY_LENGTH; k++) {
            // Write key char to storage.
            EEPROM.update(position, this->keys[i][k]);

            // Increment position.
            position++;
        }

        // Increment keys.
        keys++;
    }

    // Update key count in storage.
    EEPROM.write(0, keys);
}

/**
 * Adds key to array and storage.
 *
 * @param  String  key
 */
void KeyDB::addKey(String key) {
    // Make key fixed length.
    key = this->keyLengthen(key);

    // Set index to new value.
    int keys = this->count();
    this->keys[keys] = key;

    // Find position for next input.
    int position = (keys * DB_KEY_LENGTH) + 1;

    // Loop through the key char length.
    for(int k = 0; k < DB_KEY_LENGTH; k++) {
        // Write key char to storage.
        EEPROM.update(position, this->keys[keys][k]);

        // Increment position.
        position++;
    }

    // Update key count in storage.
    EEPROM.write(0, keys + 1);
}

/**
 * Removes key from array and shift indexes. 
 *
 * @param  String  key
 */
void KeyDB::removeKey(String key) {
    // Make key fixed length.
    key = this->keyLengthen(key);

    // Loop through keys.
    int shifting = 0;
    for (int i = 0; i < DB_KEY_MAX; i++) {
        // Shift indexes if shifting.
        if (shifting) 
            this->keys[i - 1] = this->keys[i];

        // Break out of loop if empty.
        if (this->keys[i] == "")
            break;

        // Continue if not same key.
        if (this->keys[i] != key)
            continue;

        // Start shifting indexes.
        shifting = 1;
    }
}

/**
 * Checks if key exists in array.
 *
 * @param  String  key
 * @return bool
 */
bool KeyDB::keyExists(String key) {
    // Make key fixed length.
    key = this->keyLengthen(key);

    // Loop through keys.
    for (int i = 0; i < DB_KEY_MAX; i++) {
        // Return out of array if empty.
        if (this->keys[i] == "")
            return false;

        // Return found status if same key.
        if (this->keys[i] == key) {
            return true;
        }
    }
}

/**
 * Forces a key to a fixed defined length.
 *
 * @param  String  key
 * @return String
 */
String KeyDB::keyLengthen(String key) {
    // Add zeros untill correct char length.
    while (key.length() < DB_KEY_LENGTH) {
        key = '0' + key;
    }

    // Return key with fixed length.
    return key;
}
