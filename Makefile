# --- Макроси ---
CC     = gcc
# -Wall      : показувати всі основні попередження
# -IHeader   : шукати заголовні файли (funcs.h) у каталозі Header
CFLAGS = -Wall -IHeader

all: lab7

# --- Виконуваний файл ---
# Залежить від main.o та бібліотеки libfuncs.so.
# -L.      : каталог з бібліотеками — поточний (крапка)
# -lfuncs  : підключити libfuncs.so (префікс lib і розширення не пишуться)
# -lm      : математична бібліотека (потрібна для pow)
# -Wl,-rpath,. : передати лінкеру опцію -rpath з аргументом "." —
#                під час запуску завантажувач шукатиме .so і в поточному каталозі.
#                Без цього програма не запуститься: бібліотеки немає в /lib чи /usr/lib.
lab7: main.o libfuncs.so
	$(CC) -o lab7 main.o -L. -l:libfuncs.so -lm -Wl,-rpath,.

# --- Об'єктний файл main.c ---
# -c : тільки компіляція, без лінкування. Перебудовується, якщо змінився main.c або funcs.h
main.o: Source/main.c Header/funcs.h
	$(CC) $(CFLAGS) -c Source/main.c -o main.o

# --- Динамічна бібліотека ---
# -shared : створити спільну бібліотеку (.so), а не виконуваний файл
# -lm     : залежність бібліотеки від math
libfuncs.so: funcs.o
	$(CC) -shared -o libfuncs.so funcs.o -lm

# --- Об'єктний файл funcs.c ---
# -fPIC — обов'язковий для .so
funcs.o: Source/funcs.c Header/funcs.h
	$(CC) $(CFLAGS) -fPIC -c Source/funcs.c -o funcs.o

# --- Видалення ---
# -f : не видавати помилку, якщо файлів немає
clean:
	rm -f *.o *.so lab7