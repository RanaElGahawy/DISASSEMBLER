SRC_FILES = $(shell find ./ -name '*.cpp')
OUTPUT= rvcdiss

compile:	$(SRC_FILES)
	g++ $(SRC_FILES) -o $(OUTPUT)


CTest:
	g++ main.cpp compressed.cpp -o $(OUTPUT)

ATest:
	g++ main1.cpp ThirtyTwoBit.cpp 32_bit.cpp -o $(OUTPUT)


clean:
	$(RM) $(OUTPUT)
