# VectorClass

## Programos tikslas

- veikimas kaip std::vector

## Idiegimas (Unix kompiuteryje) 

- `git clone https://github.com/ToNyHasK/VectorClass.git`
- `cd VectorClass`

## Versiju istorija (changelog)

### [v0.3](https://github.com/ToNyHasK/VectorClass/releases/tag/v0.3) - (2019-05-27)

**Pataisyta**

- vectoriaus atminties perskirstymas

**Pridėta**

- vector<studentas> laiko skaičiavimas

|perskirstymu ir laiko skaiciavimas su std::vector(int, stud) ir Class vector(int, stud)|
|-----------------------------------------------------------------
|std::vector capacity: 134217728 std::vector perskirstymu skaicius(int): 28
|Vector capacity: 136216564 Vector perskirstymu skaicius(int):44
|Laiko matavimas su std::vector(int)
|Elapsed time with size of: 10000 std::vector(int): 0 s
|Elapsed time with size of: 10000 Class vector(int): 0 s
|Elapsed time with size of: 100000 std::vector(int): 0.0019944 s
|Elapsed time with size of: 100000 Class vector(int): 0.0011221 s
|Elapsed time with size of: 1000000 std::vector(int): 0.0221155 s
|Elapsed time with size of: 1000000 Class vector(int): 0.0092758 s
|Elapsed time with size of: 10000000 std::vector(int): 0.220563 s
|Elapsed time with size of: 10000000 Class vector(int): 0.0944828 s
|Elapsed time with size of: 100000000 std::vector(int): 2.13769 s
|Elapsed time with size of: 100000000 Class vector(int): 1.07763 s
|Elapsed time with size of: 10000 std::vector(studentas): 0.0110627 s
|Elapsed time with size of: 10000 Class vector(studentas): 0.0090333 s

### [v0.2](https://github.com/ToNyHasK/VectorClass/releases/tag/v0.2) - (2019-05-19)

**Pataisyta**

- Readme 

**Prideta**

- Kiek kartu paskirsto atminti

**Atminties paskirstymo tikrinimas**

- std::vector capacity: 134217728 std::vector perskirstymu skaicius: 28

- class Vector capacity: 268435456 class Vector perskirstymu skaicius:13


### [v0.1](https://github.com/ToNyHasK/VectorClass/releases/tag/v0.1) - (2019-05-18)

**Funkciju apra�ymas**

- **operator=**: priskiria konteineriui reik�me
- **front**: prieiga prie pirmo elemento
- **emty**: patikrina ar konteineris tu�cias
- **insert**: prideda elementus
- **push_back**: prideda elementus i pabaiga
- **swap**: sukeicia turini
- **begin cbegin**:gra�ina iteratoriu i prad�ia

**Laiko tikrinimas**

- std::vector:
	-su sz = 10000: 0.0004956 s
	-su sz = 100000: 0.0029757 s
	-su sz = 1000000: 0.0198145 s
	-su sz = 10000000: 0.201875 s
	-su sz = 100000000: 1.89571 s
- class Vector:
	-su sz = 10000: 0.0 s
	-su sz = 100000: 0.0009922 s
	-su sz = 1000000: 0.006447 s
	-su sz = 10000000: 0.0624899 s
	-su sz = 100000000: 0.816916 s

**Laiko tikrinimas treciojoje u�d.**

- std::vector:
	- whole program with 100000 students: 4.65151 s
- class Vector:
	- whole program with 100000 students: 4.82345 s