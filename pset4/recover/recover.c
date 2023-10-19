#include <stdio.h>
#include <stdlib.h>

// usage ./recover [file_to_recover]

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");

    if (raw == NULL)
    {
        return 1;
    }

    int jpg_header[4] = {0xff, 0xd8, 0xff, 0xe0};
    int chank_size = 512;
    unsigned char *temp_data = malloc(512);

    int file_id = 0;
    FILE *img;
    char file_name[8];

    while (fread(temp_data, 512, 1, raw))
    {

        if (temp_data[0] == 0xff)
        {
            if (temp_data[1] == 0xd8)
            {
                if (temp_data[2] == 0xff)
                {
                    if ((temp_data[3] & 0xf0) == 0xe0)
                    {

                        if (file_id > 0)
                        {
                            fclose(img);
                        }
                        sprintf(file_name, "%03d.jpg", file_id);
                        img = fopen(file_name, "w");
                        file_id++;
                    }
                }
            }
        }
        if (file_id > 0)
        {
            fwrite(temp_data, 512, 1, img);
        }
    }

    fclose(raw);
    fclose(img);
    free(temp_data);
    return 0;
}