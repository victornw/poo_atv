EXECUTABLE = bidu_beauty_store

# Arquivos de código fonte
SRCS = bidu_beauty.cpp

# Flags de compilação
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Regra padrão
all: $(EXECUTABLE)

# Regra para compilar o executável
$(EXECUTABLE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras para limpar o executável
clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean