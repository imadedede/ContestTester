CXX = clang++
OPT = -std=gnu++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer

CHECK = ./check.py
TARGET = a b c d e f g h i j k l m n o p q r s t u v w x y z

all: $(TARGET)

$(TARGET): FORCE
	$(CXX) $(BOOST_LDFLAGS) $(BOOST_CXXFLAGS) $(OPT) -o $@ $@.cpp
	$(CHECK) $@

FORCE:
.PHONY: FORCE

