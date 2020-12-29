#pragma once
#include <iostream>
#include <fstream>
using namespace std;

const int ARRAY_SIZE = 8;

template<class ItemType>
struct ChunkArray
{
	// values keeps track of how many values there are in each chunk
	int values = 0;

	ItemType chunk[ARRAY_SIZE] = { 0,0,0,0,0,0,0,0 };
	ChunkArray<ItemType>* next;
};

template<class ItemType>
class ChunkList
{
public:
	ChunkList();
	~ChunkList();
	void Append(ItemType elem);

	int GetLength();
	int GetIndex_value(int i);
	bool Contains(ItemType elem);
	void Print(ostream& out);
	void Remove(ItemType elem);
	bool IsEmpty();


private:
	ChunkArray<ItemType>* head;
	ChunkArray<ItemType>* tail;

	int TotLength;

	//ItemType ChunkArray[ARRAY_SIZE];
};

// Class constructor
template<class ItemType>
ChunkList<ItemType>::ChunkList()
{

	tail = NULL;
	head = NULL;
	// next = nullptr;
	// next = NULL;
	TotLength = 0;


}
// Class deconstructor
template<class ItemType>
inline ChunkList<ItemType>::~ChunkList()
{
	ChunkArray<ItemType>* temp = head;
	while (head != nullptr) {
		head = head->next;
		delete temp;
		temp = head;
	}
}

// Pre: Array exists to append to
// Post: will append value to list

template<class ItemType>
void ChunkList<ItemType>::Append(ItemType elem)
{
	// if head is null then add a new chunk + increment length by 1 for each added element
	if (head == nullptr) {

		head = new ChunkArray<ItemType>;
		// will make sure that it is appended to end of chunk
		tail = head;
		head->chunk[head->values] = elem;
		head->values += 1;
		head->next = nullptr;
		TotLength += 1;

	}
	
	else {
		// declaration of increment pointer to head to traverse list
		ChunkArray<ItemType>* increment = head;
		while (increment != nullptr) {
			// condition that chunk is not full
			if (increment->values < ARRAY_SIZE) {
				increment->chunk[increment->values] = elem;
				increment->values += 1;
				// will this below satement get me the current size of the chunk?
				// given that i have initialized int len as a private variable in the class?			
				TotLength += 1;
				break;
			}
			// condition that chunk is full and increment is at last element 

			else if (increment == tail) {
				// will create a new chunk when it gets to this point
				cout << "creating new chunk" << endl;

				tail->next = new ChunkArray<ItemType>();
				tail = tail->next;
				increment = tail;
				increment->chunk[increment->values] = elem;
				increment->values += 1;
				TotLength += 1;
				break;
			}
			else {
				increment = increment->next;
			}
		}

	}


}
//Pre: TotLength is decremented or incremented in other functions
//Post: will return the total length of list
template<class ItemType>
int ChunkList<ItemType>::GetLength()
{
	return TotLength;
}
// Pre: appended value exists 
//Post: will return the item at index value given
template<class ItemType>
int ChunkList<ItemType>::GetIndex_value(int i)
{
	int current = 0;
	
	ChunkArray<ItemType>* curr = head;
	// current is a counter of the index

	while (current <= i && curr != nullptr) {
		if (i > ChunkList::TotLength - 1) {
			cerr << "OUT OF BOUNDS!" << endl;
			break;
		}

		// seeing if i is at least ARRAY_SIZE more than current 
		// skip chunk if that is the case
		
		else if (i - current >= ARRAY_SIZE && curr->values == ARRAY_SIZE) {
			curr = curr->next;
			current += ARRAY_SIZE;
		}
		// checking for where "current" is
		// certain that i is in this location of array

		else {
			// returning the item at the index provided by argument
			// current is used as an offset to find the exact location

			return curr->chunk[i - current];
		}

	}


}



// returns true if the elem is in one of the chunks

//Pre: list exists
//Post: will return bool to finding first instance of item
template<class ItemType>
bool ChunkList<ItemType>::Contains(ItemType elem)
{
	

	//find element
	ChunkArray<ItemType>* increment = head;
	// break when element found
	while (increment != nullptr) {
		
		for (int i = 0; i < ARRAY_SIZE; i++) {
			
			if (increment->chunk[i] == elem) {
				return true;
			}
		}
	increment = increment->next;
	}
	
	return false;
}



template<class ItemType>
inline void ChunkList<ItemType>::Print(ostream& out)
{
	//Pre: a proper function argument. and list exists
	//Post: will post list to the stream
	for (int i = 0; i < ChunkList::TotLength; i++) {
		out << ChunkList::GetIndex_value(i) << endl;
		// out << cout << ChunkList::GetIndex(i) << endl;
	}

}

template<class ItemType>
inline void ChunkList<ItemType>::Remove(ItemType elem)
{

	//Pre: element is stated in test file
	//Post: will remove item from list and update the list count
	ChunkArray<ItemType>* find_element = head;
	ChunkArray<ItemType>* previous = head;
	int array_size_count = 8;

	while (find_element != nullptr) {
		for (int i = 0; i < array_size_count; i++) {
			//sorted array slide code here
			
			// checking if node length is less than 2 (not equal to 1)
			if (find_element->chunk[i] == elem && find_element->values != 1) {
				if (i < array_size_count) {
					array_size_count -= 1;
					for (int j = i; j < array_size_count; j++) {
						find_element->chunk[j] = find_element->chunk[j + 1];
							
					}
					find_element->values -= 1;
					TotLength -= 1;
					return;
				}

			}

			
			
			else if (find_element->chunk[i] == elem && find_element == head) {
				// assuming there is only one element and only one chunk
				if (find_element->next == NULL) {
					find_element->values -= 1;

				}
				// if there are more chunks(nodes) after the head
				else {
					previous = head;
					head = head->next;

					delete previous;

				}

				TotLength -= 1;
				return;
			}

			
			
			// delete a node from a link list
			else if (find_element->chunk[i] == elem) {
			
					previous->next = find_element->next;
					// only applies if find_element is tail
					if (find_element == tail) {
						tail = previous;
					}
					// house keeping
					delete find_element;
					TotLength -= 1;
					return;
			}
		
						
		}
		
		//goes to next chunk after it is done cycling through the values of the first chunk
		previous = find_element;
		find_element = find_element->next;
	}
}







template<class ItemType>
inline bool ChunkList<ItemType>::IsEmpty()
{
	return ChunkList::GetLength() == 0;
}
