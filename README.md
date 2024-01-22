# cholesky

## ocb
wszystko jest podzielone na tematyczne moduły (table ma funkcje do tablic graph do grafu). nie ma klas, user data typy opierają się na `using` (lepszy typedef / aliasowanie) i funkcje pozaklasowe. nie jest to idealne rozwiązanie ale nikt na to nie będzie raczej patrzył po semestrze (update jednak ktoś będzie, przepraszam)

## building

```
mkdir build
cd build
cmake ..
make
```

wtedy plik `cholesky` to binarka z mainem. przy dodawaniu nowych plików źródłowych z rozszerzeniem .c należy je dodać do `CMakeLists.txt`. można to pewnie zrobić automatycznie ale nie zostało to ustawione.

jeżeli ktoś to czyta, to tak nie powinno się pisać kodu, nie ma klas, nie ma namespaceów i wszystko podawane jest przez wartość co trochę spowalnia program, morał dla potomnych - róbcie klasy róbcie namespacey i podawajcie przez referencję kiedy się da
