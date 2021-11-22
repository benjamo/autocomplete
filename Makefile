CC=g++
CPPFLAGS=-I.
DEPS = TrieNode.h Trie.h
OBJ = autocomplete.o TrieNode.o Trie.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

autocomplete: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f *.o autocomplete 
