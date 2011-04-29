        #include "BinaryLLHeap.h"
        #include "dsexceptions.h"

        /**
         * Construct the binary heap.
         * capacity is the capacity of the binary heap.
         */
        template <class Comparable>
        BinaryLLHeap<Comparable>::BinaryLLHeap():root(NULL), last(NULL)
        {
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         * Duplicates are allowed.
         * Throw Overflow if container is full.
         */
        template <class Comparable>
        void BinaryLLHeap<Comparable>::insert( const Comparable & x )
        {
          if(isEmpty())
            root = last = new BinaryLLHeapNode(NULL, x)
          else
          {
                // Percolate up
            BinaryLLHeadNode <Comparable> *ptr = last;
            while(ptr->parent)
            {
              ptr = ptr->parent;
              if(!ptr->left || !ptr->right)
                break;
            }
            // Now at root or an external node
            if(!ptr-
            int hole = ++currentSize;
            for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
                array[ hole ] = array[ hole / 2 ];
            array[ hole ] = x;
        }

        /**
         * Find the smallest item in the priority queue.
         * Return the smallest item, or throw Underflow if empty.
         */
        template <class Comparable>
        const Comparable & BinaryLLHeap<Comparable>::findMin( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return array[ 1 ];
        }

        /**
         * Remove the smallest item from the priority queue.
         * Throw Underflow if empty.
         */
        template <class Comparable>
        void BinaryLLHeap<Comparable>::deleteMin( )
        {
            if( isEmpty( ) )
                throw Underflow( );

            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        /**
         * Remove the smallest item from the priority queue
         * and place it in minItem. Throw Underflow if empty.
         */
        template <class Comparable>
        void BinaryLLHeap<Comparable>::deleteMin( Comparable & minItem )
        {
            if( isEmpty( ) )
                throw Underflow( );

            minItem = array[ 1 ];
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        /**
         * Establish heap order property from an arbitrary
         * arrangement of items. Runs in linear time.
         */
        template <class Comparable>
        void BinaryLLHeap<Comparable>::buildHeap( )
        {
            for( int i = currentSize / 2; i > 0; i-- )
                percolateDown( i );
        }

        /**
         * Test if the priority queue is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Comparable>
        bool BinaryLLHeap<Comparable>::isEmpty( ) const
        {
            return root == NULL;
        }



        /**
         * Make the priority queue logically empty.
         */
        template <class Comparable>
        void BinaryLLHeap<Comparable>::makeEmpty( )
        {
          currentSize = 0;
        }

        /**
         * Internal method to percolate down in the heap.
         * hole is the index at which the percolate begins.
         */
        template <class Comparable>
        void BinaryLLHeap<Comparable>::percolateDown( int hole )
        {
             int child;
            Comparable tmp = array[ hole ];

          for( ; hole * 2 <= currentSize; hole = child )
            {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
              child++;
          if( array[ child ] < tmp )
              array[ hole ] = array[ child ];
                else
              break;
            }
      array[ hole ] = tmp;
        }

