# Deck Finder

Deck Finder is a software to find good decks to play Hearthstone or rate a given one.

## Getting Started

In your 'build' folder you need to have the following files and folders in this structure.
```
data/
--->*cards.json
--->*cards.collectible.json
--->HSReplay/
------->**(Here must be files with valid statistic results structure from ___).
--->CollectOBot/
------->**(Here must be files with valid statistic results structure from CollectOBot).
```
*From HearthstoneJSON.

**In case you need it.


### Prerequisites

Before mentioned "cards.json" and "cards.collectible.json" updated from https://hearthstonejson.com/.

In the same way you need statistic result files from ___ or http://www.hearthscry.com/CollectOBot depending on what you need.

### Installing

You only need to compile and include the files and folders structure before mentioned. 

CMake compilation tested with GNU 7.3.0 on Linux and MSVC 15.8.

## Use

All the excecutable files have their specific instructions in their folders.
