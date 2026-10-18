# --- Макроси ---
# Компілятор
CC     = gcc
# -Wall      : показувати всі основні попередження
# -IHeader   : шукати заголовні файли (funcs.h) у каталозі Header
CFLAGS = -Wall -IHeader

all: lab7

# --- Виконуваний файл ---
# Залежить від main.o та бібліотеки libfuncs.a.
# -L.      : каталог з бібліотеками — поточний (крапка)
# -lfuncs  : підключити бібліотеку libfuncs.a
# -lm      : математична бібліотека (потрібна для pow)
lab7: main.o libfuncs.a
	$(CC) -o lab7 main.o -L. -l:libfuncs.a -lm

# --- Об'єктний файл main.c ---
# -c : тільки компіляція, без лінкування. Перебудовується, якщо змінився main.c або funcs.h
main.o: Source/main.c Header/funcs.h
	$(CC) $(CFLAGS) -c Source/main.c -o main.o

# --- Статична бібліотека ---
# ar cr : створити архів (c — створити, r — додати/замінити файли)
libfuncs.a: funcs.o
	ar cr libfuncs.a funcs.o

# --- Об'єктний файл funcs.c ---
funcs.o: Source/funcs.c Header/funcs.h
	$(CC) $(CFLAGS) -c Source/funcs.c -o funcs.o
	
# --- Видалення ---
# -f : не видавати помилку, якщо файлів немає
clean:
	rm -f *.o *.a lab7