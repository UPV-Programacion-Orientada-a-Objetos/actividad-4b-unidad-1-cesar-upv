#include <iostream>
#include <iomanip>
#include "Simulador2D.h"

int main()
{
    std::cout << "--- Simulador Generico de Fluidos (Difusion) ---\n"
              << std::endl;

    std::cout << ">> Inicializando Sistema (Tipo FLOAT) <<" << std::endl;
    std::cout << "Creando Grid (FLOAT) de 5x5...\n"
              << std::endl;

    Simulador2D<float> sim(5, 5);

    std::cout << ">> Agregando Fuentes de Concentracion <<" << std::endl;
    sim.agregarFuente(100.0f);
    std::cout << "Agregar Fuente 1 (Valor 100.0): Exito." << std::endl;
    sim.agregarFuente(50.0f);
    std::cout << "Agregar Fuente 2 (Valor 50.0): Exito.\n"
              << std::endl;

    std::cout << ">> Aplicando Valores Iniciales <<" << std::endl;
    sim.setValor(2, 2, 100.0f);
    std::cout << "Grid[2,2] = 100.0 (Fuente 1)" << std::endl;
    sim.setValor(4, 0, 50.0f);
    std::cout << "Grid[4,0] = 50.0 (Fuente 2)\n"
              << std::endl;

    int pasoActual = 0;
    int opcion;

    do
    {
        std::cout << "\n--- Menu ---" << std::endl;
        std::cout << "1. Visualizar Grid" << std::endl;
        std::cout << "2. Establecer Valor en Celda" << std::endl;
        std::cout << "3. Simular 1 Paso" << std::endl;
        std::cout << "4. Redimensionar Grid" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            std::cout << "\n--- Grid Inicial (Paso " << pasoActual << ") ---" << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            sim.imprimirGrid();
            break;

        case 2:
        {
            int fila, col;
            float valor;
            std::cout << "Fila: ";
            std::cin >> fila;
            std::cout << "Columna: ";
            std::cin >> col;
            std::cout << "Valor: ";
            std::cin >> valor;
            sim.setValor(fila, col, valor);
            std::cout << "Valor establecido." << std::endl;
            break;
        }

        case 3:
            std::cout << "\nSimulando Propagacion..." << std::endl;
            sim.simularPaso();
            pasoActual++;
            std::cout << "\n--- Grid Despues del Paso " << pasoActual << " ---" << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            sim.imprimirGrid();
            break;

        case 4:
        {
            int nuevaF, nuevaC;
            std::cout << "Nuevas filas: ";
            std::cin >> nuevaF;
            std::cout << "Nuevas columnas: ";
            std::cin >> nuevaC;
            sim.redimensionarGrid(nuevaF, nuevaC);
            std::cout << "Redimensionando Grid a " << nuevaF << "x" << nuevaC << ". Datos copiados." << std::endl;
            break;
        }

        case 0:
            std::cout << "\nLiberando memoria del Grid y Fuentes... Sistema cerrado." << std::endl;
            break;

        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}