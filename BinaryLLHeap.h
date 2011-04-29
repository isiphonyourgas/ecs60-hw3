        #ifndef _BINARY_LL_HEAP_H_
        #define _BINARY_LL_HEAP_H_

        #define NULL 0



        // BinaryLLHeap class
        //
        // CONSTRUCTION: with a negative infinity sentinel and
        //               optional capacity (that defaults to 100)
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Throws Underflow and Overflow as warranted
        template <class Comparable>  class BinaryLLHeap;

        template <class Comparable>
        class BinaryLLHeapNode
        {
          BinaryLLHeapNode *parent, *left, *right;
          Comparable data;
          BinaryLLHeapNode(BinaryLLHeapNode<Comparable> p, const Comparable &d):
            parent(p), left(NULL), right(NULL), data(d)
          {
          }
          friend class BinaryLLHeap<Comparable>;
        };

        template <class Comparable>
        class BinaryLLHeap
        {
          public:
            explicit BinaryLLHeap();

            bool isEmpty( ) const;
            const Comparable & findMin( ) const;

            void insert( const Comparable & x );
            void deleteMin( );
            void deleteMin( Comparable & minItem );
            void makeEmpty( );

          private:
            BinaryLLHeapNode <Comparable> *root, *last;

            void buildHeap( );
            void percolateDown( int hole );
        };

        #include "BinaryLLHeap.cpp"
        #endif
