#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

#define BUFFER_SIZE 42

// Función para comparar strings
int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Función para imprimir resultados de test
void print_test_result(const char *test_name, int result)
{
    if (result == 0)
        printf("✅ %s: PASÓ\n", test_name);
    else
        printf("❌ %s: FALLÓ\n", test_name);
}

// Test 1: Lectura básica de archivo
int test_basic_reading(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return 1;
    
    char *line;
    int line_count = 0;
    char *expected_lines[] = {
        "Primera línea",
        "Segunda línea", 
        "Tercera línea",
        "Cuarta línea",
        NULL
    };
    
    while ((line = get_next_line(fd)) != NULL)
    {
        if (expected_lines[line_count] == NULL)
        {
            free(line);
            close(fd);
            return 1; // Demasiadas líneas
        }
        
        if (ft_strcmp(line, expected_lines[line_count]) != 0)
        {
            free(line);
            close(fd);
            return 1; // Línea incorrecta
        }
        
        free(line);
        line_count++;
    }
    
    close(fd);
    return (line_count == 4) ? 0 : 1;
}

// Test 2: Archivo vacío
int test_empty_file()
{
    // Crear archivo vacío temporal
    FILE *temp = fopen("temp_empty.txt", "w");
    if (!temp)
        return 1;
    fclose(temp);
    
    int fd = open("temp_empty.txt", O_RDONLY);
    if (fd == -1)
        return 1;
    
    char *line = get_next_line(fd);
    close(fd);
    unlink("temp_empty.txt");
    
    return (line == NULL) ? 0 : 1;
}

// Test 3: Archivo con una sola línea
int test_single_line()
{
    // Crear archivo con una línea
    FILE *temp = fopen("temp_single.txt", "w");
    if (!temp)
        return 1;
    fprintf(temp, "Una sola línea");
    fclose(temp);
    
    int fd = open("temp_single.txt", O_RDONLY);
    if (fd == -1)
        return 1;
    
    char *line = get_next_line(fd);
    int result = (line != NULL && ft_strcmp(line, "Una sola línea") == 0) ? 0 : 1;
    
    free(line);
    close(fd);
    unlink("temp_single.txt");
    
    return result;
}

// Test 4: Archivo con líneas vacías
int test_empty_lines()
{
    // Crear archivo con líneas vacías
    FILE *temp = fopen("temp_empty_lines.txt", "w");
    if (!temp)
        return 1;
    fprintf(temp, "Línea 1\n\nLínea 3\n\n");
    fclose(temp);
    
    int fd = open("temp_empty_lines.txt", O_RDONLY);
    if (fd == -1)
        return 1;
    
    char *line;
    int line_count = 0;
    char *expected[] = {"Línea 1\n", "\n", "Línea 3\n", "\n", NULL};
    
    while ((line = get_next_line(fd)) != NULL)
    {
        if (expected[line_count] == NULL)
        {
            free(line);
            close(fd);
            unlink("temp_empty_lines.txt");
            return 1;
        }
        
        if (ft_strcmp(line, expected[line_count]) != 0)
        {
            free(line);
            close(fd);
            unlink("temp_empty_lines.txt");
            return 1;
        }
        
        free(line);
        line_count++;
    }
    
    close(fd);
    unlink("temp_empty_lines.txt");
    return (line_count == 4) ? 0 : 1;
}

// Test 5: Múltiples descriptores de archivo
int test_multiple_fds()
{
    // Crear dos archivos diferentes
    FILE *temp1 = fopen("temp_fd1.txt", "w");
    FILE *temp2 = fopen("temp_fd2.txt", "w");
    if (!temp1 || !temp2)
        return 1;
    
    fprintf(temp1, "Archivo 1\nLínea 2\n");
    fprintf(temp2, "Archivo 2\nLínea 2\nLínea 3\n");
    fclose(temp1);
    fclose(temp2);
    
    int fd1 = open("temp_fd1.txt", O_RDONLY);
    int fd2 = open("temp_fd2.txt", O_RDONLY);
    
    if (fd1 == -1 || fd2 == -1)
        return 1;
    
    char *line1 = get_next_line(fd1);
    char *line2 = get_next_line(fd2);
    
    int result = 0;
    if (ft_strcmp(line1, "Archivo 1\n") != 0 || ft_strcmp(line2, "Archivo 2\n") != 0)
        result = 1;
    
    free(line1);
    free(line2);
    
    // Leer más líneas
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    
    if (ft_strcmp(line1, "Línea 2\n") != 0 || ft_strcmp(line2, "Línea 2\n") != 0)
        result = 1;
    
    free(line1);
    free(line2);
    
    close(fd1);
    close(fd2);
    unlink("temp_fd1.txt");
    unlink("temp_fd2.txt");
    
    return result;
}

// Test 6: Descriptor de archivo inválido
int test_invalid_fd()
{
    char *line = get_next_line(-1);
    return (line == NULL) ? 0 : 1;
}

// Test 7: Archivo muy grande
int test_large_file()
{
    // Crear archivo con muchas líneas
    FILE *temp = fopen("temp_large.txt", "w");
    if (!temp)
        return 1;
    
    for (int i = 0; i < 1000; i++)
    {
        fprintf(temp, "Línea %d del archivo grande\n", i);
    }
    fclose(temp);
    
    int fd = open("temp_large.txt", O_RDONLY);
    if (fd == -1)
        return 1;
    
    char *line;
    int line_count = 0;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
        line_count++;
    }
    
    close(fd);
    unlink("temp_large.txt");
    
    return (line_count == 1000) ? 0 : 1;
}

// Función principal
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("❌ Uso: %s <archivo_test>\n", argv[0]);
        return 1;
    }
    
    printf("🧪 Iniciando pruebas de Get Next Line...\n\n");
    
    int total_tests = 0;
    int passed_tests = 0;
    
    // Ejecutar todos los tests
    int result;
    
    result = test_basic_reading(argv[1]);
    print_test_result("Lectura básica", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    result = test_empty_file();
    print_test_result("Archivo vacío", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    result = test_single_line();
    print_test_result("Una sola línea", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    result = test_empty_lines();
    print_test_result("Líneas vacías", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    result = test_multiple_fds();
    print_test_result("Múltiples descriptores", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    result = test_invalid_fd();
    print_test_result("Descriptor inválido", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    result = test_large_file();
    print_test_result("Archivo grande", result);
    if (result == 0) passed_tests++;
    total_tests++;
    
    printf("\n📊 Resultados:\n");
    printf("   Total de pruebas: %d\n", total_tests);
    printf("   ✅ Exitosas: %d\n", passed_tests);
    printf("   ❌ Fallidas: %d\n", total_tests - passed_tests);
    
    if (passed_tests == total_tests)
    {
        printf("\n🎉 ¡Todas las pruebas de Get Next Line pasaron!\n");
        return 0;
    }
    else
    {
        printf("\n⚠️  Algunas pruebas fallaron\n");
        return 1;
    }
} 