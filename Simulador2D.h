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
    // ... otros métodos de acceso y visualización
};

// * Constructor (asignación de memoria e inicialización)
template <typename T>
Simulador2D<T>::Simulador2D(int f, int c) : _grid(nullptr), _filas(f), _columnas(c),
                                            _fuentes(nullptr), _numFuentes(0), _capacidadFuentes(0),
                                            _constantes{1.0f, 1.0f, 1.0f} // valores por defecto: dif=1, dx=1, dt=1
{
    if (_filas < 0) {
        _filas = 0;
    }
        
    if (_columnas < 0) {
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

#endif