#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

template <typename T>
class Simulador2D
{
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

public:
    // MÉTODOS PÚBLICOS OBLIGATORIOS:
    Simulador2D(int f, int c); // Constructor
    ~Simulador2D();            // Destructor
    void redimensionarGrid(int nuevaF, int nuevaC);
    void agregarFuente(T valor); // Expansión manual del vector dinámico si es necesario
    void simularPaso();          // Implementación del algoritmo

    // Métodos auxiliares para acceso y visualización
    void setValor(int fila, int col, T valor);
    T getValor(int fila, int col) const;
    void imprimirGrid() const;
    int getFilas() const { return _filas; }
    int getColumnas() const { return _columnas; }
};

// * Constructor (asignación de memoria e inicialización)
template <typename T>
Simulador2D<T>::Simulador2D(int f, int c) : _grid(nullptr), _filas(f), _columnas(c),
                                            _fuentes(nullptr), _numFuentes(0), _capacidadFuentes(0),
                                            _constantes{1.0f, 1.0f, 1.0f} // valores por defecto: dif=1, dx=1, dt=1
{
    if (_filas < 0)
    {
        _filas = 0;
    }

    if (_columnas < 0)
    {
        _columnas = 0;
    }

    // asignación de la matriz 2D
    if (_filas > 0 && _columnas > 0)
    {
        _grid = new T *[_filas];
        for (int i = 0; i < _filas; ++i)
        {
            _grid[i] = new T[_columnas];
        }
        // inicializar el grid a valor por defecto de T (cero para tipos numéricos)
        for (int i = 0; i < _filas; ++i)
        {
            for (int j = 0; j < _columnas; ++j)
            {
                _grid[i][j] = T();
            }
        }
    }
    else
    {
        _grid = nullptr;
        _filas = 0;
        _columnas = 0;
    }

    // asignación inicial del vector dinámico de fuentes
    _capacidadFuentes = 2; // capacidad mínima inicial
    _fuentes = new T[_capacidadFuentes];
    _numFuentes = 0;
}

// * Destructor (liberación de memoria)
template <typename T>
Simulador2D<T>::~Simulador2D()
{
    // liberar memoria de la matriz
    if (_grid)
    {
        for (int i = 0; i < _filas; ++i)
        {
            delete[] _grid[i];
        }
        delete[] _grid;
        _grid = nullptr;
    }

    // liberar fuentes
    if (_fuentes)
    {
        delete[] _fuentes;
        _fuentes = nullptr;
    }
}

// * agregarFuente (expansión manual del vector)
template <typename T>
void Simulador2D<T>::agregarFuente(T valor)
{
    // verificar si se necesita expandir la capacidad
    if (_numFuentes >= _capacidadFuentes)
    {
        // duplicar la capacidad
        int nuevaCapacidad = _capacidadFuentes * 2;

        // crear nuevo array con mayor capacidad
        T *nuevoArray = new T[nuevaCapacidad];

        // copiar los datos antiguos al nuevo array
        for (int i = 0; i < _numFuentes; ++i)
        {
            nuevoArray[i] = _fuentes[i];
        }

        // liberar el array antiguo
        delete[] _fuentes;

        // actualizar el puntero y la capacidad
        _fuentes = nuevoArray;
        _capacidadFuentes = nuevaCapacidad;
    }

    // agregar el nuevo valor
    _fuentes[_numFuentes] = valor;
    _numFuentes++;
}

// * redimensionarGrid
template <typename T>
void Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC)
{
    // validar dimensiones
    if (nuevaF < 0)
    {
        nuevaF = 0;
    }
    if (nuevaC < 0)
    {
        nuevaC = 0;
    }

    // crear la nueva matriz
    T **nuevoGrid = nullptr;

    if (nuevaF > 0 && nuevaC > 0)
    {
        nuevoGrid = new T *[nuevaF];
        for (int i = 0; i < nuevaF; ++i)
        {
            nuevoGrid[i] = new T[nuevaC];
            // inicializar a valor por defecto
            for (int j = 0; j < nuevaC; ++j)
            {
                nuevoGrid[i][j] = T();
            }
        }

        // copiar datos del grid antiguo al nuevo (hasta donde sea posible)
        if (_grid)
        {
            int filasACopiar = (_filas < nuevaF) ? _filas : nuevaF;
            int columnasACopiar = (_columnas < nuevaC) ? _columnas : nuevaC;

            for (int i = 0; i < filasACopiar; ++i)
            {
                for (int j = 0; j < columnasACopiar; ++j)
                {
                    nuevoGrid[i][j] = _grid[i][j];
                }
            }
        }
    }

    // liberar el grid antiguo
    if (_grid)
    {
        for (int i = 0; i < _filas; ++i)
        {
            delete[] _grid[i];
        }
        delete[] _grid;
    }

    // actualizar puntero y dimensiones
    _grid = nuevoGrid;
    _filas = nuevaF;
    _columnas = nuevaC;
}

// * setValor (establecer valor en una celda)
template <typename T>
void Simulador2D<T>::setValor(int fila, int col, T valor)
{
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas)
    {
        _grid[fila][col] = valor;
    }
}

// * getValor (obtener valor de una celda)
template <typename T>
T Simulador2D<T>::getValor(int fila, int col) const
{
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas)
    {
        return _grid[fila][col];
    }
    return T(); // retornar valor por defecto si está fuera de rango
}

// * imprimirGrid
template <typename T>
void Simulador2D<T>::imprimirGrid() const
{
    for (int i = 0; i < _filas; ++i)
    {
        std::cout << "| ";
        for (int j = 0; j < _columnas; ++j)
        {
            std::cout << _grid[i][j];
            if (j < _columnas - 1)
            {
                std::cout << " | ";
            }
        }
        std::cout << " |" << std::endl;
    }
}

#endif