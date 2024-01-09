CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto
INCLUDE_PATHS = -I/opt/homebrew/include

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f main
