// UNIVA Guadalajara.
// Diseño y programación estructurada de software Irving Edgar Mendoza Ayala.
// Katya Aimé Ramírez Vázquez & Fernanda Bracho Guitron .
// Proyecto final: Gestión de Calificaciones y Asistencias para profesores de lengua extranjeta Inglés 
// GTS: Grade Track System.

#include <stdio.h>
#include <stdlib.h>
#define MAX_ALUMNOS 35
#define LIMITE_FALTAS 8
#define LONGITUD_CONTRASENA 20
#define LONGITUD_NOMBRE 30
#define MAX_INTENTOS 3

typedef struct { //estructura principal del programa
    char nombre[LONGITUD_NOMBRE];
    char apellido[LONGITUD_NOMBRE];
    int inasistencias_parcial1;
    int inasistencias_parcial2;
    int inasistencias_parcial3;
    float notas_parcial1[6];
    float notas_parcial2[6];
    float notas_parcial3[3];
    float promedio_parcial1;
    float promedio_parcial2;
    float promedio_parcial3;
    float promedio_final;
    int reprobado;
    int parciales_capturados[3];
} Alumno;

Alumno lista_alumnos[MAX_ALUMNOS];
int total_alumnos = 0;
int usuario_actual = 0;

// Prototipos de funciones
void limpiarBuffer();
int esNumero(const char* cadena);
int compararCadenas(const char* cad1, const char* cad2);
void mostrarMarcoBoleta(const char* titulo);
void generarBoletaProfesor(const char* nombre, const char* apellido);
void mostrarRubros();
void generarBoletaCursos();
void menuCoordinacion();
int autenticarUsuario();
float calcularParcial12(int parcial, int alumno_idx);
float calcularParcial3(int alumno_idx);
void aplicarReglasInasistencias(int alumno_idx);
void verificarReprobacion(int alumno_idx);
void capturarCalificaciones();
void mostrarReprobados();
void generarBoletaIndividual();
void generarArchivoExcel();
void registrarAlumnos();
void menuPrincipal();

void limpiarBuffer() { //Limpia informacion 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int esNumero(const char* cadena) { //cuenta cifras
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] < '0' || cadena[i] > '9') return 0;
    }
    return 1;
}

int compararCadenas(const char* cad1, const char* cad2) { //compaara cadenas
    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0') {
        if (cad1[i] != cad2[i]) return 0;
        i++;
    }
    return (cad1[i] == '\0' && cad2[i] == '\0');
}

void mostrarMarcoBoleta(const char* titulo) { //muestra el marco de la boleta con ascii
    printf("%c", 218);
    for(int i = 0; i < 38; i++) printf("%c", 196);
    printf("%c\n", 191);
    
    printf("%c %-36s %c\n", 179, titulo, 179);
    
    printf("%c", 192);
    for(int i = 0; i < 38; i++) printf("%c", 196);
    printf("%c\n", 217);
}

void generarBoletaProfesor(const char* nombre, const char* apellido) {
    system("cls");
    mostrarMarcoBoleta("BOLETA DE PROFESOR");
    printf("Nombre: %s %s\n", nombre, apellido);
    printf("Idioma: Ingl%cs\n",130);
    printf("Nivel: 8\n");
    printf("Categor%ca: Business Model\n",161);
    
    mostrarMarcoBoleta("RUBROS POR PARCIAL");
    printf("Parcial 1 y 2:\n");
    printf("- Tareas y actividades (10%%)\n");
    printf("- Participaci%cn (10%%)\n",162);
    printf("- Proyecto integrador (10%%)\n");
    printf("- Habilidades (20%%)\n");
    printf("- Examen oral (20%%)\n");
    printf("- Examen escrito (30%%)\n\n");
    
    printf("Parcial 3:\n");
    printf("- Proyecto integrador (50%%)\n");
    printf("- Habilidades (20%%)\n");
    printf("- Examen escrito (30%%)\n");
    
    system("pause");
}

void mostrarRubros() { //muestra los rubros
    system("cls");
    printf("--- RUBROS GENERALES ---\n\n");
    printf("Parcial 1 y 2:\n");
    printf("- Tareas y actividades: 10%%\n");
    printf("- Participaci%cn: 10%%\n",162);
    printf("- Proyecto integrador: 10%%\n");
    printf("- Habilidades: 20%%\n");
    printf("- Examen oral: 20%%\n");
    printf("- Examen escrito: 30%%\n\n");
    
    printf("Parcial 3:\n");
    printf("- Proyecto integrador: 50%%\n");
    printf("- Habilidades: 20%%\n");
    printf("- Examen escrito: 30%%\n");
    
    system("pause");
}

void generarBoletaCursos() { //genera boleta
    system("cls");
    mostrarMarcoBoleta("BOLETA DE CURSOS");
    printf("Cursos impartidos:\n");
    printf("- Profesor: Nadezhda Zemlyanskova\n");
    printf("- Profesor: Alfredo Ruiz\n");
    printf("Idioma: Ingl%cs\n",130);
    printf("Nivel: 8\n");
    printf("Categor%ca: Business Model\n",161);
    
    system("pause");
}

void menuCoordinacion() { // menu unico para coordinacion
    int opcion;
    char input[10];
    
    do {
        system("cls");
        printf("--- MENU COORDINACION ---\n");
        printf("1. Visualizar profesores\n");
        printf("2. Visualizar rubros\n");
        printf("3. Generar boleta de cursos\n");
        printf("4. Generar archivo Excel (informaci%cn de profesores y cursos)\n",162);
        printf("5. Salir\n");
        printf("Opci%cn: ",162);
        
        scanf("%9s", input);
        limpiarBuffer();
        
        if(!esNumero(input) || (opcion = atoi(input)) < 1 || opcion > 5) {
            printf("Opci%cn no valida,ingrese una opci%cn de las listadas anteriormente (1-6).\n",162,162);
            system("pause");
            continue;
        }
        
        switch(opcion) {
            case 1: {
                int sub_opcion;
                do {
                    system("cls");
                    printf("--- VISUALIZAR PROFESORES ---\n");
                    printf("1. Nadezhda Zemlyanskova\n");
                    printf("2. Alfredo Ruiz\n");
                    printf("3. Volver al men%c anterior\n",163);
                    printf("Opci%cn: ",162);
                    scanf("%9s", input);
                    limpiarBuffer();
                    sub_opcion = atoi(input);
                    
                    if (sub_opcion == 1 || sub_opcion == 2) {
                        const char* nombre = (sub_opcion == 1) ? "Nadezhda" : "Alfredo";
                        const char* apellido = (sub_opcion == 1) ? "Zemlyanskova" : "Ruiz";
                        generarBoletaProfesor(nombre, apellido);
                    } else if (sub_opcion == 3) {
                        break;
                    } else {
                        printf("Opci%cn inv%clida,ingrese una de las opciones anteriormente mostradas (1-2).\n",162,160);
                        system("pause");
                    }
                } while(1);
                break;
            }
            case 2:
                mostrarRubros();
                break;
            case 3:
                generarBoletaCursos();
                break;
            case 4:
                generarArchivoExcel();
                break;
            case 5:
                printf("Saliendo...\n");
                return;
        }
    } while(opcion != 5);
}

int autenticarUsuario() { //usuarios y sus contras
    int intentos = 0;
    int id;
    char pass[LONGITUD_CONTRASENA];
    const char* usuarios[3] = {"NadezhdaZ18", "AlfredoR", "CELE4"};
    const char* nombres[3] = {"Nadezhda Z.", "Alfredo R.", "Coordinacion"}; //no supe ponerle acento lol
    
    do {
        system("cls");
        printf("--- SISTEMA DE GESTION ACADEMICA ---\n\n");
        
        char input[10];
        do {
            printf("Ingrese su n%cmero de usuario (1-3): ",163);
            scanf("%9s", input);
            limpiarBuffer();
            
            if (!esNumero(input) || (id = atoi(input)) < 1 || id > 3) {
                printf("Usuario no v%clido. Intente nuevamente, ingrese una de las opciones anteriormente mostradas (1-3).\n",160);
            } else break;
        } while(1);
        
        printf("Ingrese su contrase%ca: ",164);
        scanf("%19s", pass);
        limpiarBuffer();
        
        if (compararCadenas(pass, usuarios[id-1])) {
            usuario_actual = id;
            printf("\nBienvenido, %s\n", nombres[id-1]);
            system("pause");
            return 1;
        } else {
            printf("Contrase%ca incorrecta. Intentos restantes: %d\n",164,MAX_INTENTOS-intentos-1);
            intentos++;
            system("pause");
        }
    } while(intentos < MAX_INTENTOS);
    
    return 0;
}
float calcularParcial12(int parcial, int alumno_idx) { 
    float *notas = (parcial == 1) ? lista_alumnos[alumno_idx].notas_parcial1 
                                  : lista_alumnos[alumno_idx].notas_parcial2;
    char input[10];

    printf("\n--- Captura de notas (Parcial %d) ---\n", parcial);
    printf("Alumno: %s %s\n", lista_alumnos[alumno_idx].nombre, lista_alumnos[alumno_idx].apellido);

    const char* rubros[6] = {
        "Tareas y actividades (10%): ",
        "Participacion (10%): ",
        "Proyecto integrador (10%): ",
        "Habilidades (20%): ",
        "Examen oral (20%): ",
        "Examen escrito (30%): "
    };

    float max_values[6] = {10, 10, 10, 20, 20, 30};

    for (int i = 0; i < 6; i++) {
        do {
            printf("%s (Ingrese 0-%.0f): ", rubros[i], max_values[i]); 
            scanf("%9s", input);
            limpiarBuffer();

            if (!esNumero(input)) {
                printf("Ingrese un n%cmero v%clido.\n", 163, 160);
            } else {
                notas[i] = atof(input);
                if (notas[i] < 0 || notas[i] > max_values[i]) {
                    printf("La nota debe estar entre 0 y %.0f.\n", max_values[i]);
                } else break;
            }
        } while (1);
    }

    
    char input_inasistencias[10];  //funcion repetida??? pq esta doble 
    int inasistencias;
    do {
        printf("Inasistencias para parcial %d: ", parcial);
        scanf("%9s", input_inasistencias);
        limpiarBuffer();
        
        if(!esNumero(input_inasistencias) || (inasistencias = atoi(input_inasistencias)) < 0) {
            printf("Valor no v%clido. Ingrese un numero entero no negativo.\n",160);
        } else {
            if(parcial == 1) lista_alumnos[alumno_idx].inasistencias_parcial1 = inasistencias;
            else lista_alumnos[alumno_idx].inasistencias_parcial2 = inasistencias;
            break;
        }
    } while(1);
    
    float promedio = (notas[0]/10*0.1) + (notas[1]/10*0.1) + (notas[2]/10*0.1) + 
                    (notas[3]/20*0.2) + (notas[4]/20*0.2) + (notas[5]/30*0.3);
    float promedio_porcentaje = promedio * 100;
    
    if(usuario_actual == 2) {
        promedio_porcentaje -= (inasistencias * 1.0);
        if(promedio_porcentaje < 0) promedio_porcentaje = 0;
    }
    
    if(parcial == 1) lista_alumnos[alumno_idx].promedio_parcial1 = promedio_porcentaje;
    else lista_alumnos[alumno_idx].promedio_parcial2 = promedio_porcentaje;
    
    return promedio_porcentaje;
}

float calcularParcial3(int alumno_idx) { //funcion especifica para calcular parcial 3
    float *notas = lista_alumnos[alumno_idx].notas_parcial3;
    char input[10];
    
    printf("\n--- Captura de notas (Parcial 3) ---\n");
    printf("Alumno: %s %s\n", lista_alumnos[alumno_idx].nombre, lista_alumnos[alumno_idx].apellido);
    
    const char* rubros[3] = {
        "Proyecto integrador (50%): ",
        "Habilidades (20%): ",
        "Examen escrito (30%): "
    };
    
    float max_values[3] = {50,20,30}; //listado de limites para calificaciones
    
    for(int i = 0; i < 3; i++) {
        do {
            printf("%s (Ingrese 0-%.0f): ", rubros[i], max_values[i]);
            scanf("%9s", input);
            limpiarBuffer();
            
            if(!esNumero(input)) {
                printf("Ingrese un n%cmero v%clido.\n",163,160);
            } else {
                notas[i] = atof(input);
                if(notas[i] < 0 || notas[i] > max_values[i]) {
                    printf("La nota debe estar entre 0 y %.0f.\n", max_values[i]);
                } else break;
            }
        } while(1);
    }
    
    char input_inasistencias[10]; 
    int inasistencias;
    do {
        printf("Inasistencias para parcial 3: ");
        scanf("%9s", input_inasistencias);
        limpiarBuffer();
        
        if(!esNumero(input_inasistencias) || (inasistencias = atoi(input_inasistencias)) < 0) {
            printf("Valor no v%clido. Ingrese un n%cmero entero no negativo.\n",160,163);
        } else {
            lista_alumnos[alumno_idx].inasistencias_parcial3 = inasistencias;
            break;
        }
    } while(1);
    
    float promedio = (notas[0]/50*0.5) + (notas[1]/20*0.2) + (notas[2]/30*0.3);
    float promedio_porcentaje = promedio * 100;
    
    if(usuario_actual == 2) {
        promedio_porcentaje -= (inasistencias * 1.0);
        if(promedio_porcentaje < 0) promedio_porcentaje = 0;
    }
    
    lista_alumnos[alumno_idx].promedio_parcial3 = promedio_porcentaje;
    return promedio_porcentaje;
}

void aplicarReglasInasistencias(int alumno_idx) {
    Alumno *a = &lista_alumnos[alumno_idx];
    
    if(usuario_actual == 1) {
        int total = a->inasistencias_parcial1 + a->inasistencias_parcial2 + a->inasistencias_parcial3;
        if(total >= 4) {
            a->promedio_final -= 1.0;
            if(a->promedio_final < 0) a->promedio_final = 0;
        }
    }
}

void verificarReprobacion(int alumno_idx) { //sirve para verificar si estan reprobados 
    Alumno *a = &lista_alumnos[alumno_idx];
    int total_inasistencias = a->inasistencias_parcial1 + 
                            a->inasistencias_parcial2 + 
                            a->inasistencias_parcial3;
    float suma_parciales = (a->promedio_parcial1 / 10) + 
                          (a->promedio_parcial2 / 10) + 
                          (a->promedio_parcial3 / 10);
    
    a->reprobado = (total_inasistencias >= LIMITE_FALTAS) || 
                   (a->promedio_final < 6.0) || 
                   (suma_parciales < 18.0);
}

void capturarCalificaciones() { ///captura las notas y tiene verificacion para que no vuelva a insertar notas si es que ya las inserto
    system("cls");

    if(total_alumnos == 0) {
        printf("No hay alumnos registrados.\n");
        system("pause");
        return;
    }

    printf("--- CAPTURA DE CALIFICACIONES ---\n\n");
    printf("Lista de alumnos:\n");

    for(int i = 0; i < total_alumnos; i++) {
        printf("%d. %s %s\n", i + 1, lista_alumnos[i].nombre, lista_alumnos[i].apellido);
    }

    int alumno_idx;
    char input[10];

    do {
        printf("\nSeleccione alumno (1-%d): ", total_alumnos);
        scanf("%9s", input);
        limpiarBuffer();

        if(!esNumero(input) || (alumno_idx = atoi(input)) < 1 || alumno_idx > total_alumnos) {
            printf("Selecci%cn no v%clida.\n",162,160);
        } else {
            alumno_idx--; // Ajustar índice para coincidir con el array
            break;
        }
    } while(1);

    // Usar el arreglo de parciales capturados
    int *parciales_capturados = lista_alumnos[alumno_idx].parciales_capturados;

    int opcion;
    do {
        printf("\nSeleccione parcial (1-3) o ingrese 0 para salir: ");
        scanf("%9s", input);
        limpiarBuffer();

        if(!esNumero(input)) {
            printf("Opci%cn no v%clida, ingrese una opción válida (1-3 o 0 para salir).\n",162,160);
            continue;
        }

        opcion = atoi(input);

      
        if(opcion == 0) {
            printf("Proceso de captura de calificaciones cancelado.\n");
            break;
        }

        
        if (opcion < 1 || opcion > 3) {
            printf("Opci%cn no válida, ingrese una opción válida (1-3).\n",162);
            continue;
        }
         // Validar si el parcial ya fue capturado
        if (parciales_capturados[opcion - 1] == 1) {
            printf("Ya se ha capturado ese parcial anteriormente, registre otro (Parcial 1, 2 o 3 seg%cn corresponda).\n",163);
            continue;
        }

        break;
    } while(1);

    
    if(opcion == 0) {
        return;
    }

   
    if(opcion == 1 || opcion == 2) {
        calcularParcial12(opcion, alumno_idx);
    } else {
        calcularParcial3(alumno_idx);
    }

    
    parciales_capturados[opcion - 1] = 1;

   
    lista_alumnos[alumno_idx].promedio_final =
        (lista_alumnos[alumno_idx].promedio_parcial1 * 0.3 +
         lista_alumnos[alumno_idx].promedio_parcial2 * 0.3 +
         lista_alumnos[alumno_idx].promedio_parcial3 * 0.4);

    aplicarReglasInasistencias(alumno_idx);
    verificarReprobacion(alumno_idx);

    printf("\nCaptura completada para %s %s.\n", 
           lista_alumnos[alumno_idx].nombre, lista_alumnos[alumno_idx].apellido);
    system("pause");
}

void mostrarReprobados() {//muestra lo antes calculado en la funcion verficarreprobados
    system("cls");
    printf("--- ALUMNOS REPROBADOS ---\n\n");
    
    int encontrados = 0;
    for(int i = 0; i < total_alumnos; i++) {
        if(lista_alumnos[i].reprobado) {
            int total = lista_alumnos[i].inasistencias_parcial1 + 
                       lista_alumnos[i].inasistencias_parcial2 + 
                       lista_alumnos[i].inasistencias_parcial3;
            printf("%d. %s %s - Inasistencias: %d - Promedio: %.1f/10\n", 
                   i+1, lista_alumnos[i].nombre, lista_alumnos[i].apellido,
                   total, lista_alumnos[i].promedio_final);
            encontrados++;
        }
    }
    
    if(encontrados == 0) printf("No hay reprobados.\n");
    system("pause");
}

void generarBoletaIndividual() { //genera la boleta de los alumnos 
    system("cls");
    if(total_alumnos == 0) {
        printf("No hay alumnos registrados.\n");
        system("pause");
        return;
    }
    
    printf("--- BOLETA INDIVIDUAL ---\n\n");
    int id;
    char input[10];
    do {
        printf("Ingrese n%cmero de alumno (1-%d): ",163,total_alumnos);
        scanf("%9s", input);
        limpiarBuffer();
        
        if(!esNumero(input) || (id = atoi(input)) < 1 || id > total_alumnos) {
            printf("N%cmero no v%clido.\n",163,160);
        } else break;
    } while(1);
    
    Alumno a = lista_alumnos[id-1];
    system("cls");
    
    int total_inasistencias = a.inasistencias_parcial1 + 
                            a.inasistencias_parcial2 + 
                            a.inasistencias_parcial3;
    
    mostrarMarcoBoleta("BOLETA DE CALIFICACION");
    printf("Alumno: %d\n", id);
    printf("Nombre: %s %s\n", a.nombre, a.apellido);
    printf("Inasistencias: %d\n", total_inasistencias);
    
    mostrarMarcoBoleta("CALIFICACIONES PARCIALES");
    printf("Parcial 1: %.1f/10\n", a.promedio_parcial1 / 10);
    printf("Parcial 2: %.1f/10\n", a.promedio_parcial2 / 10);
    printf("Parcial 3: %.1f/10\n", a.promedio_parcial3 / 10);
    
    mostrarMarcoBoleta("PROMEDIO FINAL");
    printf("Promedio: %.1f/100\n", a.promedio_final);
    printf("Estado: %s\n", (a.promedio_final == 0 || a.promedio_final < 60) ? "REPROBADO" : "APROBADO"); //correcion de linea pone limite     
    system("pause");
}

 
void generarArchivoExcel() { //funcion de respaldo
    system("cls");
    char nombreArchivo[30];
    
    if(usuario_actual == 3) {
        // Archivo para coordinación (profesores y cursos)
        sprintf(nombreArchivo, "informacion_coordinacion.csv");
        
        FILE *archivo = fopen(nombreArchivo, "w");
        if(archivo == NULL) {
            printf("Error al crear archivo\n");
            system("pause");
            return;
        }
        
        fprintf(archivo, "Tipo,Nombre,Apellido,Idioma,Nivel,Categoria\n");
        fprintf(archivo, "Profesor,Nadezhda,Zemlyanskova,Ingles,8,Business Model\n");
        fprintf(archivo, "Profesor,Alfredo,Ruiz,Ingles,8,Business Model\n");
        fprintf(archivo, "Curso,,,Ingles,8,Business Model\n");
        
        fclose(archivo);
        printf("Archivo generado: %s\n", nombreArchivo);
    } else {
        // Archivo para profesores (alumnos)
        if(total_alumnos == 0) {
            printf("No hay alumnos registrados.\n");
            system("pause");
            return;
        }
        
        sprintf(nombreArchivo, "calificaciones_usuario%d.csv", usuario_actual);
        
        FILE *archivo = fopen(nombreArchivo, "w");
        if(archivo == NULL) {
            printf("Error al crear archivo\n");
            system("pause");
            return;
        }
        
        fprintf(archivo, "Nombre,Apellido,Inasistencias,"
                       "P1_Tareas,P1_Participacion,P1_Proyecto,P1_Habilidades,P1_Oral,P1_Escrito,"
                       "P2_Tareas,P2_Participacion,P2_Proyecto,P2_Habilidades,P2_Oral,P2_Escrito,"
                       "P3_Proyecto,P3_Habilidades,P3_Escrito,"
                       "PromParcial1,PromParcial2,PromParcial3,PromedioFinal,Estado\n");
        
        for(int i = 0; i < total_alumnos; i++) {
            int total_inasistencias = lista_alumnos[i].inasistencias_parcial1 + 
                                    lista_alumnos[i].inasistencias_parcial2 + 
                                    lista_alumnos[i].inasistencias_parcial3;
            
            fprintf(archivo, "%s,%s,%d,"
                           "%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,"
                           "%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,"
                           "%.1f,%.1f,%.1f,"
                           "%.1f,%.1f,%.1f,%.1f,%s\n",
                    lista_alumnos[i].nombre,
                    lista_alumnos[i].apellido,
                    total_inasistencias,
                    
                    lista_alumnos[i].notas_parcial1[0],
                    lista_alumnos[i].notas_parcial1[1],
                    lista_alumnos[i].notas_parcial1[2],
                    lista_alumnos[i].notas_parcial1[3],
                    lista_alumnos[i].notas_parcial1[4],
                    lista_alumnos[i].notas_parcial1[5],
                    
                    lista_alumnos[i].notas_parcial2[0],
                    lista_alumnos[i].notas_parcial2[1],
                    lista_alumnos[i].notas_parcial2[2],
                    lista_alumnos[i].notas_parcial2[3],
                    lista_alumnos[i].notas_parcial2[4],
                    lista_alumnos[i].notas_parcial2[5],
                    
                    lista_alumnos[i].notas_parcial3[0],
                    lista_alumnos[i].notas_parcial3[1],
                    lista_alumnos[i].notas_parcial3[2],
                    
                    lista_alumnos[i].promedio_parcial1 / 10,
                    lista_alumnos[i].promedio_parcial2 / 10,
                    lista_alumnos[i].promedio_parcial3 / 10,
                    lista_alumnos[i].promedio_final,
                    lista_alumnos[i].reprobado ? "Reprobado" : "Aprobado");
        }
        
        fclose(archivo);
        printf("Archivo generado: %s\n", nombreArchivo);
    }
    
    system("pause");
}

void registrarAlumnos() { 
    system("cls");
    printf("--- REGISTRO DE ALUMNOS ---\n\n");

    if (total_alumnos >= MAX_ALUMNOS) {
        printf("No se pueden registrar m%cs alumnos. L%cmite alcanzado.\n", 160, 161);
        system("pause");
        return;
    }

    char input[10];
    int nuevos_alumnos;
    do {
        printf("N%cmero de nuevos alumnos (m%cx %d, disponibles %d): ", 163, 160, MAX_ALUMNOS, MAX_ALUMNOS - total_alumnos);
        scanf("%9s", input);
        limpiarBuffer();

        if (!esNumero(input) || (nuevos_alumnos = atoi(input)) < 1 || (total_alumnos + nuevos_alumnos) > MAX_ALUMNOS) {
            printf("Cantidad no v%clida.\n", 160);
        } else break;
    } while (1);

    for (int i = 0; i < nuevos_alumnos; i++) {
        int idx = total_alumnos + i; // Nuevo índice sin sobrescribir los existentes - correcion para la no escritura

        printf("\nAlumno %d:\n", idx + 1);
        printf("Nombre: ");
        scanf("%29s", lista_alumnos[idx].nombre);
        limpiarBuffer();

        printf("Apellido: ");
        scanf("%29s", lista_alumnos[idx].apellido);
        limpiarBuffer();

        lista_alumnos[idx].inasistencias_parcial1 = 0;
        lista_alumnos[idx].inasistencias_parcial2 = 0;
        lista_alumnos[idx].inasistencias_parcial3 = 0;
        lista_alumnos[idx].promedio_parcial1 = 0;
        lista_alumnos[idx].promedio_parcial2 = 0;
        lista_alumnos[idx].promedio_parcial3 = 0;
        lista_alumnos[idx].promedio_final = 0;
        lista_alumnos[idx].reprobado = 0;
    }

    total_alumnos += nuevos_alumnos; // Incrementamos la cantidad total sin perder datos

    printf("\nRegistro completado.\n");
    system("pause");
}

void menuPrincipal() { //menu de acciones principales
    int opcion;
    char input[10];
    
    do {
        system("cls");
        printf("--- MENU PRINCIPAL ---\n");
        printf("Usuario: %s\n", usuario_actual == 1 ? "Nadezhda Z." : "Alfredo R."); // if rapido
        printf("1. Registrar alumnos\n");
        printf("2. Capturar calificaciones\n");
        printf("3. Mostrar reprobados\n");
        printf("4. Generar boleta\n");
        printf("5. Generar Excel\n");
        printf("6. Salir\n");
        printf("Opci%cn: ",162);
        
        scanf("%9s", input);
        limpiarBuffer();
        
        if(!esNumero(input) || (opcion = atoi(input)) < 1 || opcion > 6) {
            printf("Opci%cn no v%clida.\n",162,160);
            system("pause");
            continue;
        }
        
        switch(opcion) {
            case 1: registrarAlumnos(); break;
            case 2: capturarCalificaciones(); break;
            case 3: mostrarReprobados(); break;
            case 4: generarBoletaIndividual(); break;
            case 5: generarArchivoExcel(); break;
            case 6: printf("Saliendo...\n"); break;
        }
    } while(opcion != 6);
}

int main() { //donde se despliega los menus principales 
    if(!autenticarUsuario()) {
        printf("Demasiados intentos fallidos. Saliendo.\n");
        return 1;
    }
    
    if (usuario_actual == 3) {
        menuCoordinacion();
    } else {
        menuPrincipal();
    }
    return 0;
}