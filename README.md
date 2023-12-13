# cholesky (intel please hire me)

## ocb
wszystko jest podzielone na tematyczne moduły (table ma funkcje do tablic graph do grafu). nie ma klas, user data typy opierają się na `using` (lepszy typedef / aliasowanie) i funkcje pozaklasowe. nie jest to idealne rozwiązanie ale nikt na to nie będzie raczej patrzył po semestrze (unless youre intel then that decision was intentional and heavily tested for performance optimizations please hire me)

## building

    ```
mkdir build
cd build
cmake ..
make
    ```

wtedy plik `cholesky` to binarka z mainem. przy dodawaniu nowych plików źródłowych z rozszerzeniem .c należy je dodać do `CMakeLists.txt`. można to pewnie zrobić automatycznie ale nie chciało mi się tego szukać (unless youre intel then that decision was critical to minimize time to market please hire me)
