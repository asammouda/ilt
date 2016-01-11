#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define LG_BUFFER 64

// Sur les Raspberry Pi modele 1 (A et B), la LED est connectee a la sortie GPIO 16.
// Sur les Raspberry Pi modeles 1 B+ et 2, la LED est connectee a la sortie GPIO 47.
// Ajustez la ligne suivante en fonction de votre carte de TP.
#define GPIO_LED  16

int main(void)
{
	int i;
	int v = 0;
	int fd;
	char buffer[LG_BUFFER];

	// Retirer le module leds_gpio.ko s'il est charge
	system("rmmod leds_gpio 2> /dev/null");

	// Exporter la GPIO de la LED dans /sys
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		perror("unable to open gpio/export");
		exit(EXIT_FAILURE);
	}
	snprintf(buffer, LG_BUFFER, "%d", GPIO_LED);
	write(fd, buffer, strlen(buffer));
	// On ne verifie pas les echecs.
	// 	Si la GPIO est deja exportee, tant mieux.
	//	Si l'export est impossible on aura une erreur ensuite.
	close(fd);

	// Basculer la GPIO en sortie.
	snprintf(buffer, LG_BUFFER, "/sys/class/gpio/gpio%d/direction", GPIO_LED);
	fd = open(buffer, O_WRONLY);
	if (fd < 0) {
		perror("unable to open GPIO direction");
		exit(EXIT_FAILURE);
	}
	if (write(fd, "out", 3) < 0) {
		perror("unable to set GPIO direction");
		exit(EXIT_FAILURE);
	}
	close(fd);

	// Clignoter en accelerant.
	snprintf(buffer, LG_BUFFER, "/sys/class/gpio/gpio%d/value", GPIO_LED);
	fd = open(buffer, O_WRONLY);
	if (fd < 0) {
		perror("unable to open GPIO value");
		exit(EXIT_FAILURE);
	}
	while(1) {
		v = 0;
		for (i = 1; i < 50; i ++) {
			snprintf(buffer, LG_BUFFER, "%d", v);
			pwrite(fd, buffer, strlen(buffer), 0);
			usleep(1000000 / i);
			v = 1 - v;
		}
	}

	close(fd);
	return EXIT_SUCCESS;
}

