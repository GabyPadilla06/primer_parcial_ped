#include <iostream>
#include <cmath>

using namespace std;

struct PuntoTrayectoria
{
    string identificadorPunto;
    string nombrePunto;
    float coordernadas[3];
    float distancia;
    string clasificacionPunto;
};

void registrarPunto(PuntoTrayectoria &punto);
float calcularDistancia(PuntoTrayectoria *punto);
void clasificarPunto(PuntoTrayectoria &punto);
PuntoTrayectoria *obtenerPuntoMasAlejado(PuntoTrayectoria puntos[], int cantidad);
void corregirCoordenadas(PuntoTrayectoria &punto, float desplazamientoX, float desplazamientoY, float desplazamientoZ);
void generarInforme(PuntoTrayectoria puntos[],int cantidad);

int main()
{

    const int maximoPuntos = 10;
    PuntoTrayectoria puntos[maximoPuntos];
    int cantidad = 0;

    do
    {
        cout << "Ingrese la cantidad de puntos a registrar (1-" << maximoPuntos << "): ";
        cin >> cantidad;

        if (cantidad < 1 || cantidad > maximoPuntos)
        {
            cout << "Cantidad invalida. Intente de nuevo" << endl;
            cantidad = 0;
        }

    } while (cantidad < 1 || cantidad > maximoPuntos);

    cout << "Registro de puntos" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        cout << "Punto #" << (i + 1) << endl;
        registrarPunto(puntos[i]);

        float distancia = calcularDistancia(puntos + i);
        cout << "La distancia es: " << distancia << endl;

        clasificarPunto(puntos[i]);
    }

    cout << "Informe de promedio de puntos: "<<endl; 
    generarInforme(puntos, cantidad);
    cout << "----------------------------------"<<endl<<endl; 

    PuntoTrayectoria *puntoMayor = obtenerPuntoMasAlejado(puntos, cantidad);

    if (puntoMayor != nullptr)
    {
        float nuevaX = 0.0;
        float nuevaY = 0.0;
        float nuevaZ = 0.0;

        cout << "El punto con mayor distancia es: " << endl;
        cout << "ID: " << puntoMayor->identificadorPunto << endl;
        cout << "Nombre: " << puntoMayor->nombrePunto << endl;
        cout << "Coordernada X: " << puntoMayor->coordernadas[0] << endl;
        cout << "Coordernada Y: " << puntoMayor->coordernadas[1] << endl;
        cout << "Coordernada Z: " << puntoMayor->coordernadas[2] << endl;
        cout << "Distancia: " << puntoMayor->distancia << endl;
        cout << "Distancia: " << puntoMayor->clasificacionPunto << endl << endl;

        cout << "Ingresa el desplazamiento de la coordenada X: ";
        cin >> nuevaX;
        cout << "Ingresa el desplazamiento de la coordenada Y: ";
        cin >> nuevaY;
        cout << "Ingresa el desplazamiento de la coordenada Z: ";
        cin >> nuevaZ;

        calcularDistancia(puntoMayor);
        clasificarPunto(*puntoMayor);

        cout << "El punto con mayor distancia es: " << endl;
        cout << "ID: " << puntoMayor->identificadorPunto << endl;
        cout << "Nombre: " << puntoMayor->nombrePunto << endl;
        cout << "Coordernada X: " << puntoMayor->coordernadas[0] << endl;
        cout << "Coordernada Y: " << puntoMayor->coordernadas[1] << endl;
        cout << "Coordernada Z: " << puntoMayor->coordernadas[2] << endl;
        cout << "Distancia: " << puntoMayor->distancia << endl;
        cout << "Clasificacion: " << puntoMayor->clasificacionPunto << endl << endl;

        cout << "Informe de promedio de puntos: "<<endl;
        generarInforme(puntos, cantidad);
    }

    return 0;
};

void registrarPunto(PuntoTrayectoria &punto)
{
    cout << "Ingrese el identificador del punto: " << endl;
    cin >> punto.identificadorPunto;

    cout << "Ingrese el nombre del punto: " << endl;
    cin.ignore();
    getline(cin, punto.nombrePunto);

    for (int i = 0; i < 3; i++)
    {
        cout << "Ingrese el punto " << (i + 1) << ": ";
        cin >> punto.coordernadas[i];
    }
};

float calcularDistancia(PuntoTrayectoria *punto)
{
    float x = punto->coordernadas[0];
    float y = punto->coordernadas[1];
    float z = punto->coordernadas[2];

    punto->distancia = sqrt((x * x) + (y * y) + (z * z));

    return punto->distancia;
}

void clasificarPunto(PuntoTrayectoria &punto)
{
    if (punto.distancia <= 5)
    {
        punto.clasificacionPunto = "CERCANO";
        cout << "El punto se clasifica como: " << punto.clasificacionPunto << endl;
    }
    else if (punto.distancia > 5 && punto.distancia <= 10)
    {
        punto.clasificacionPunto = "INTERMEDIO";
        cout << "El punto se clasifica como: " << punto.clasificacionPunto << endl;
    }
    else if (punto.distancia > 10 && punto.distancia <= 20)
    {
        punto.clasificacionPunto = "LEJANO";
        cout << "El punto se clasifica como: " << punto.clasificacionPunto << endl;
    }
    else if (punto.distancia > 20)
    {
        punto.clasificacionPunto = "EXTREMO";
        cout << "El punto se clasifica como: " << punto.clasificacionPunto << endl;
    }
    else
    {
        punto.clasificacionPunto = "INVALIDO";
        cout << "El punto se clasifica como: " << punto.clasificacionPunto << endl;
    }
}

PuntoTrayectoria *obtenerPuntoMasAlejado(PuntoTrayectoria puntos[], int cantidad)
{
    if (cantidad <= 0)
    {
        return nullptr;
    }

    PuntoTrayectoria *puntoMayor = &puntos[0];

    for (int i = 1; i < cantidad; i++)
    {
        if (puntos[i].distancia > puntoMayor->distancia)
        {
            puntoMayor = &puntoMayor[i];
        }
    }

    return puntoMayor;
};

void corregirCoordenadas(PuntoTrayectoria &punto, float desplazamientoX, float desplazamientoY, float desplazamientoZ)
{
    float x = punto.coordernadas[0];
    float y = punto.coordernadas[1];
    float z = punto.coordernadas[2];

    float nuevaX = x + desplazamientoX;
    float nuevaY = y + desplazamientoY;
    float nuevaZ = x + desplazamientoZ;
}

void generarInforme(PuntoTrayectoria puntos[],int cantidad){
    if(cantidad <= 0) return;

    int cercanos = 0, intermedios = 0, lejanos = 0, extremos = 0;
    float sumaFactores = 0.0f;

    cout <<"Informe general de puntos: " <<endl;

    for (int i = 0; i < cantidad; i++) {
        float puntosPromedio = (puntos[i].coordernadas[0] + puntos[i].coordernadas[1] + puntos[i].coordernadas[2]) / 3.0f;
        
        sumaFactores += puntos[i].distancia;

        if (puntos[i].clasificacionPunto == "CERCANOS") cercanos++;
        else if (puntos[i].clasificacionPunto == "INTERMEDIOS") intermedios++;
        else if (puntos[i].clasificacionPunto == "LEJANOS") lejanos++;
        else if (puntos[i].clasificacionPunto == "EXTREMOS") extremos++;

        cout << "ID: " << puntos[i].identificadorPunto << "Nombre: " << puntos[i].nombrePunto << endl;
        cout << "Puntos Promedio: " << puntosPromedio <<endl;
        cout << "DIstancia: " << puntos[i].distancia <<endl;
        cout << "Clasificacion: " << puntos[i].clasificacionPunto <<endl;
    }
}