Binaries made with poemlib.


cmudbfill
---------

  Recommended usage:
  $./cmudbfill <path to resulting database> < <path to raw cmudict>

  Use this to convert the raw cmudict (a text file) to a database suitable for
  searching over.

  The database name should end with one of the endings described in this
  document:
  
    http://fallabs.com/kyotocabinet/api/classkyotocabinet_1_1PolyDB.html#a09384a72e6a72a0be98c80a1856f34aa
  
  If you don't feel like reading that, just make the ending .kch and
  everything will be fine.
  
  You don't really need to run this (unless there might be file-endianness
  problems) as a database is supplied in ../data/cmudict.kch.


makepronundb
------------

  Recommended usage:
  $./makepronundb <path to destination database> <path to pronunciation
    dictionary> < <text to analyse>

  This will use the pronunciation dictionary (made with cmudbfill, or just use
  ../data/cmudict.kch) to get pronunciations from the inputted text and store
  sentences with pronunciations in the destination database. If the database
  already exists, new entries will be made. Note that it will only store
  sentences for which all the words have a pronunciation in the pronunciation
  dictionary (others are discarded).


ezrhyme
-------

  Recommended usage:
  $./ezrhyme <sentence database> <pronunciation description> <number of
  sentences to output>

  The sentence database was created with makepronundb.

  The pronunciation description is a number specifying the number of syllables
  and one or more vowel phonemes. The allowed vowel phonemes are:

  Phoneme   Example   Translation
  -------   -------   -----------
  
  AA        odd       AA D
  AE        at        AE T
  AH        hut       HH AH T
  AO        ought     AO T
  AW        cow       K AW
  AY        hide      HH AY D
  EH        Ed        EH D
  ER        hurt      HH ER T
  EY        ate       EY T
  IH        it        IH T
  IY        eat       IY T
  OW        oat       OW T
  OY        toy       T OY
  UH        hood      HH UH D
  UW        two       T UW

  A more thorough description of the phonemes can be found at
  
    http://www.speech.cs.cmu.edu/cgi-bin/cmudict

  Part of the above example is from there.

  If the number of sentences to output is not present or 0, all the sentences
  found matching the pattern will be output on stdout, otherwise that many
  sentences (or just all the sentences if the number of sentences found is
  smaller) will be output.

  Here is an example of requesting 3 8-syllable sentences that have AE and IY as
  the last two syllables (the backslashes \ are necessary to treat the
  pronunciation description as one argument).

    $./ezrhyme ../data/sentence-pronounce.kch 8\ AE\ IY 3

  and a possible result is:

    NO HE DID NOT MEAN TO AT LEAST
    NOTHING SO FAR AS I CAN SEE
    WELL BUSY AND VERY HAPPY

Questions?

nicholas [dot] esterer [at] gmail [dot] com

Copyright (c) 2013 Nicholas Esterer. All rights reserved.
