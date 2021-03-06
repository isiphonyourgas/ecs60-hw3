#include "ExtendibleHash.h"
#include <bitset>

using namespace std;

int Ehash(int value, int bits) {
    int check;
    check = value >> (18 - bits);
    return check;
} // Ehash()

ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) :
bits(b), LeafSize(LSize) {
    int i;
    size = 1;
    bits = b;
    ExtendibleLeaf *ptr;
    ptr = new ExtendibleLeaf(LSize, 0, 1);
    ptr->parent = this;

    for (i = 0; i < b; i++)
        size = size * 2;

    Directory = new ExtendibleLeaf*[size];

    for (i = 0; i < size; i++) {
        Directory[i] = ptr;
    }
    LeafSize = LSize;

} // ExtendibleHash()

void ExtendibleHash::insert(const int &object) {
    int j, k;
    k = size; //Initializes k for future use
    j = 0;
    while (1) {
        j = Ehash(object, bits);
        k = (Directory[j]->insert(object));
        if (k != -1) {
            this->split(k);
            j = 0;
        } else {
            break;
        }
    }
} // insert()

void ExtendibleHash::remove(const int &object) {
    int j, k;
    k = size;
    j = 0;
    j = Ehash(object, bits);
    Directory[j]->remove(object);

} // remove()

const int & ExtendibleHash::find(const int &object) {
    int j, k;
    k = size;
    j = 0;
    j = Ehash(object, bits);
    target = Directory[j]->find(object);
    return target;
} // find()

void ExtendibleHash::split(const int &object) {
    int pos = object;
    int i = pos;
    int counter = 0;
    while (i < size) {
        if (Directory[pos] == Directory[i]) {
            counter++;
        } else {
            break;
        }
        i++;
    }//get amount of shared node
    if (counter == 1) {
        this->rehash();
    } else {
        ExtendibleLeaf *ptr = new ExtendibleLeaf(LeafSize, pos + (counter / 2), 0);
        ptr->parent = this;
        Directory[pos]->split(ptr);
        for (i = (counter / 2); i < counter; i++) {
            Directory[pos + i] = ptr;
        }//sets new ptrs
    }
} // split();

void ExtendibleHash::splitCheck() {

}

void ExtendibleHash::rehash() {
    int i;
    size = size * 2;
    ExtendibleLeaf **ptr, **temp, *ptr2;
    ptr = new ExtendibleLeaf*[size];
    bits++;
    temp = Directory;
    ptr = new ExtendibleLeaf*[size];
    ptr2 = new ExtendibleLeaf(LeafSize, 0, 1);
    ptr2->parent=this;
    for (i = 0; i < (size); i++) {
        ptr[i] = ptr2;
    }
     Directory = ptr;
    temp[0]->split2();
   
    for (i = 1; i < (size / 2); i++) {

        if(temp[i] != temp[i -1]){
            temp[i]->split2();
            delete temp[i-1];
        }

    }


    delete temp;

}

void ExtendibleHash::print() {
    int i;
    for (i = 0; i < size; i++) {
        cout << "Hash index: " << i << endl;
        Directory[i]->print();
    }
    cout << endl;
}

void ExtendibleHash::insertNext(int value, int pos) {
    int i;
    for (i = pos; i < size; i++) {
        if (Directory[pos] != Directory[i]) {
            Directory[i]->insert2(value);
            break;
        }
    }
}

ExtendibleLeaf::ExtendibleLeaf(const int LeafSize, int pos, int bit) {
    position = pos;
    bits = bit;
    content = new int[LeafSize];
    count = 0;
    size = LeafSize;
}//Extendible Leaf

void ExtendibleLeaf::insert2(int value) {
    content[count] = value;
    count++;
}

int ExtendibleLeaf::insert(int value) {
    if (count >= size) {
        return position;
    } else {
        int i=1;
        for (int j = 0; j < count; j++) {
            if (content[j] == value) {
                i = 0;
                break;
            }
        }
        if (i) {
            content[count] = value;
            count++;
        }
        return -1;
    }
}//Leaf Insert

void ExtendibleLeaf::remove(int value) {
    int i, j;
    for (i = 0; i < count; i++) {
        if ((content[i] == value) && i < (count - 1)) {
            for (j = i; j < (count - 1); j++)
                content[j] = content[j + 1];
            break;
        }
        if ((content[i] == value) && i == (count - 1))
            break;
    }
    count--;
}//Leaf Remove

void ExtendibleLeaf::split(ExtendibleLeaf *nextSibling) {
    int i;
    nextSibling->setbit(bits + 1);
    bitset < 18 > bitCheck;
    for (i = 0; i < count; i++) {
        bitCheck = content[i];

        if ((bitCheck[18 - bits] == 1) && (i != count - 1)) {
            nextSibling->insert(content[i]);
            this->remove(content[i]);
            i--;
        }

        if ((bitCheck[18 - bits] == 1) && (i == count - 1)) {
            nextSibling->insert(content[i]);
            count--;
            break;
        }
    }
    bits++;
}

const int ExtendibleLeaf::find(const int value) {
    int i;
    for (i = 0; i < count; i++) {
        if (value == content[i]) {
            return content[i];
        }
    }
    return -1;
}

void ExtendibleLeaf::setbit(int i) {
    bits = i;
}

void ExtendibleLeaf::setpos(int i) {
    position = i;
}

void ExtendibleLeaf::print() {
    int i;
    bitset < 18 > bitCheck;
    for (i = 0; i < count; i++) {
        bitCheck = content[i];
        cout << i << ". " << content[i] << "  bits: " << bitCheck << endl;
    }
}

void ExtendibleLeaf::split2() {
    int i;
    for (i = 0; i < count; i++) {
        parent->insert(content[i]);
    }
}
