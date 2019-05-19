# VectorClass

## Programos tikslas

- veikimas kaip std::vector

## Idiegimas (Unix kompiuteryje) 

- `git clone https://github.com/ToNyHasK/VectorClass.git`
- `cd VectorClass`

## Versiju istorija (changelog)

### [v0.2](https://github.com/ToNyHasK/VectorClass/releases/tag/v0.2) - (2019-05-19)

**Pataisyta**

- Readme 

**Prideta**

- Kiek kartu paskirsto atminti

**Atminties paskirstymo tikrinimas**

- std::vector capacity: 134217728 std::vector perskirstymu skaicius: 28

- class Vector capacity: 268435456 class Vector perskirstymu skaicius:13


### [v0.1](https://github.com/ToNyHasK/VectorClass/releases/tag/v0.1) - (2019-05-18)

**Funkciju aprašymas**

- **operator=**: priskiria konteineriui reikšme
- **front**: prieiga prie pirmo elemento
- **emty**: patikrina ar konteineris tušcias
- **insert**: prideda elementus
- **push_back**: prideda elementus i pabaiga
- **swap**: sukeicia turini
- **begin cbegin**:gražina iteratoriu i pradžia

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

**Laiko tikrinimas treciojoje užd.**

- std::vector:
	- whole program with 100000 students: 4.65151 s
- class Vector:
	- whole program with 100000 students: 4.82345 s