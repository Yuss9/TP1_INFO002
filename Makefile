CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto
INCLUDE_PATHS = -I/opt/homebrew/include

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -MMD -MP -c $< -o $@

clean:
	rm -f main $(OBJS) $(DEPS)

-include $(DEPS)
