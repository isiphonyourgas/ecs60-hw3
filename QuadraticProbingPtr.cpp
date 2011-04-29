        #include "QuadraticProbingPtr.h"
        #include <iostream>
        using namespace std;


        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        template <class HashedObj>
        bool QuadraticPtrHashTable<HashedObj>::isPrime( int n ) const
        {
            if( n == 2 || n == 3 )
                return true;

            if( n == 1 || n % 2 == 0 )
                return false;

            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;

            return true;
        }

        /**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        template <class HashedObj>
        int QuadraticPtrHashTable<HashedObj>::nextPrime( int n ) const
        {
            if( n % 2 == 0 )
                n++;

            for( ; !isPrime( n ); n += 2 )
                ;

            return n;
        }

        /**
         * Construct the hash table.
         */
        template <class HashedObj>
        QuadraticPtrHashTable<HashedObj>::QuadraticPtrHashTable( const HashedObj & notFound, int size )
          : array(nextPrime(size)), ITEM_NOT_FOUND( notFound )
        {
            makeEmpty( );
        }

        template <class HashedObj>
        QuadraticPtrHashTable<HashedObj>::~QuadraticPtrHashTable()
        {
          for(int i = 0; i < array.size(); i++)
            if(isActive(i))
              delete (array[i]);
        }


        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class HashedObj>
        void QuadraticPtrHashTable<HashedObj>::insert( const HashedObj & x )
        {
                // Insert x as active
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                return;
            array[ currentPos ] = new HashedObj(x);

                // Rehash; see Section 5.5
            if( ++currentSize > array.size( ) / 2 )
                rehash( );
        }

        /**
         * Expand the hash table.
         */
        template <class HashedObj>
        void QuadraticPtrHashTable<HashedObj>::rehash( )
        {
            vector<const HashedObj*> oldArray = array;

                // Create new double-sized, empty table
            array.resize( nextPrime( 2 * oldArray.size( ) ) );
            for( int j = 0; j < array.size( ); j++ )
                array[ j ] = NULL;

                // Copy table over
            currentSize = 0;
            for( int i = 0; i < oldArray.size( ); i++ )
                if( oldArray[ i ] != NULL && oldArray[i] != &ITEM_NOT_FOUND)
                    insert( *(oldArray[ i ]));
        }

        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class HashedObj>
        int QuadraticPtrHashTable<HashedObj>::findPos( const HashedObj & x ) const
        {
/* 1*/      int collisionNum = 0;
/* 2*/      int currentPos = hash( x, array.size( ) );

/* 3*/      while( array[ currentPos ] != NULL
              && array[currentPos] != &ITEM_NOT_FOUND
              && *(array[ currentPos ]) != x )
            {
/* 4*/          currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
/* 5*/          if( currentPos >= array.size( ) )
/* 6*/              currentPos -= array.size( );
            }

/* 7*/      return currentPos;
        }


        /**
         * Remove item x from the hash table.
         */
        template <class HashedObj>
        void QuadraticPtrHashTable<HashedObj>::remove( const HashedObj & x )
        {
            int currentPos = findPos( x );
            if( isActive(currentPos))
            {
              delete array[currentPos];
              array[ currentPos ] = &ITEM_NOT_FOUND;
            }
        }

        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
        const HashedObj & QuadraticPtrHashTable<HashedObj>::find( const HashedObj & x ) const
        {
            int currentPos = findPos( x );
          return (isActive(currentPos)) ? *(array[ currentPos ]) : ITEM_NOT_FOUND;
        }

        /**
         * Make the hash table logically empty.
         */
        template <class HashedObj>
        void QuadraticPtrHashTable<HashedObj>::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < array.size( ); i++ )
                array[ i ] = NULL;
        }

        /**
         * Deep copy.
         */
        template <class HashedObj>
        const QuadraticPtrHashTable<HashedObj> & QuadraticPtrHashTable<HashedObj>::
        operator=( const QuadraticPtrHashTable<HashedObj> & rhs )
        {
            if( this != &rhs )
            {
                array = rhs.array;
                currentSize = rhs.currentSize;
            }
            return *this;
        }


        /**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool QuadraticPtrHashTable<HashedObj>::isActive( int currentPos ) const
        {
            return array[ currentPos ] != NULL && array[currentPos] != &ITEM_NOT_FOUND;
        }

        /**
         * A hash routine for string objects.
         */
        template <class HashedObj>
        int QuadraticPtrHashTable<HashedObj>::hash( const string & key, int tableSize ) const
        {
            int hashVal = 0;

            for( int i = 0; i < key.length( ); i++ )
                hashVal = 37 * hashVal + key[ i ];

            hashVal %= tableSize;
            if( hashVal < 0 )
                hashVal += tableSize;

            return hashVal;
        }


        /**
         * A hash routine for ints.
         */
         template <class HashedObj>
        int QuadraticPtrHashTable<HashedObj>::hash( int key, int tableSize ) const
        {
            if( key < 0 ) key = -key;
            return key % tableSize;
        }
