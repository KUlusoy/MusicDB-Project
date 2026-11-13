#include <stdlib.h>
#include <string.h>
#include "musicdb.h"

struct MusicDB
{
    Song **songs; // points to a pointer of a song (basically acts like an array of songs)
    size_t n_songs;

    Artist **artists; // points to a pointer of an artist (like an array of artists)
    size_t n_artists;
};

MusicDB *db_create()
{
    struct MusicDB *ptr;
    ptr = malloc(sizeof(struct MusicDB));

    if (ptr == NULL) // took from slides
    {
        printf("Out of memory\n");
        return NULL;
    }
    ptr->songs = NULL;

    ptr->artists = NULL;
    ptr->n_songs = 0;
    ptr->n_artists = 0;
    return ptr;
}

void db_destroy(MusicDB *db)
{
    free(db->songs);
    free(db->artists);
    free(db->n_songs);
    free(db->n_artists);
    free(db);
}

int db_load(MusicDB *db, const char *dir)
{
    FILE *f1, *f2, *f3, *f4, *f5;
    char r1, r2, r3;
    char temp[1000];
    if (strlen(dir) > 900)
    {
        printf("Failed :( (not enough space/dir too large)\n");
        return -1;
    }
    char where1[1000];
    strcpy(where1, dir);
    strcat(where1, "/songs.txt");
    f1 = fopen(where1, "r");
    char where2[1000];
    strcpy(where2, dir);
    strcat(where2, "/artists.txt");
    f2 = fopen(where2, "r");
    char where3[1000];
    strcpy(where3, dir);
    strcat(where3, "/ratings.txt");
    f3 = fopen(where3, "r");
    char where4[1000];
    strcpy(where4, dir);
    strcat(where4, "/year.txt");
    f4 = fopen(where4, "r");
    char where5[1000];
    strcpy(where5, dir);
    strcat(where5, "/people_rated.txt");
    f5 = fopen(where5, "r");
    int lineCount1 = 0;
    int lineCount2 = 0;
    int lineCount3 = 0;
    int lineCount4 = 0;
    int lineCount5 = 0;
    if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL || f5 == NULL)
    {
        printf("Failed :( (file not found)\n");
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        fclose(f5);
        return -1;
    }
    int c1 = fgetc(f1);
    int c2 = fgetc(f2);
    int c3 = fgetc(f3);
    int c4 = fgetc(f4);
    int c5 = fgetc(f5);
    while (c1 != EOF)
    {
        if (c1 == '\n')
        {
            lineCount1++;
        }
        c1 = fgetc(f1);
    }

    while (c2 != EOF)
    {
        if (c2 == '\n')
        {
            lineCount2++;
        }
        c2 = fgetc(f2);
    }
    while (c3 != EOF)
    {
        if (c3 == '\n')
        {
            lineCount3++;
        }
        c3 = fgetc(f3);
    }

    while (c4 != EOF)
    {
        if (c4 == '\n')
        {
            lineCount4++;
        }
        c4 = fgetc(f4);
    }
    while (c5 != EOF)
    {
        if (c5 == '\n')
        {
            lineCount5++;
        }
        c5 = fgetc(f5);
    }

    if (!(lineCount1 == lineCount2 && lineCount2 == lineCount3 && lineCount3 == lineCount4 && lineCount4 == lineCount5))
    {
        printf("Failed :( (files are not the same length)\n");
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        fclose(f5);
        return -1;
    }
    // have to close them and reopen to start from top again
    fclose(f1);
    f1 = fopen(where1, "r");
    fclose(f2);
    f2 = fopen(where2, "r");
    fclose(f3);
    f3 = fopen(where3, "r");
    fclose(f4);
    f4 = fopen(where4, "r");
    fclose(f5);
    f5 = fopen(where5, "r");

    char line1[1000];
    char line2[1000];
    char line3[1000];
    char line4[1000];
    char line5[1000];
    for (int i = 0; i < lineCount4; i++)
    {
        fgets(line1, sizeof(line1), f1);
        fgets(line2, sizeof(line2), f2);
        fgets(line3, sizeof(line3), f3);
        fgets(line4, sizeof(line4), f4);
        fgets(line5, sizeof(line5), f5);

        line1[strcspn(line1, "\r\n")] = 0;
        line2[strcspn(line2, "\r\n")] = 0;
        line3[strcspn(line3, "\r\n")] = 0;
        line4[strcspn(line4, "\r\n")] = 0;
        line5[strcspn(line5, "\r\n")] = 0;

        if (db_push(db, line1, line2, atof(line3), atoi(line4), atol(line5)) != 0)
        {
            printf("Faileddd\n");
            fclose(f1);
            fclose(f2);
            fclose(f3);
            fclose(f4);
            fclose(f5);
            return -1;
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    return 0;
}

size_t db_song_count(const MusicDB *db)
{
    return db->n_songs;
}
size_t db_artist_count(const MusicDB *db)
{
    return db->n_artists;
}
const Song *db_get(const MusicDB *db, size_t i)
{
    if (i >= db->n_songs)
    {
        return NULL;
    }
    else
    {
        return db->songs[i];
    }
}
int found = 0;
int db_push(MusicDB *db, const char *title, const char *artist,
            double rating, int year, unsigned long num_rated)
{
    if (db == NULL || title == NULL || artist == NULL || rating == 0.0 || year == 0 || num_rated == 0)
    {
        return -1;
    }

    Artist *ptr = NULL;
    for (int i = 0; i < db->n_artists; i++)
    {
        if (strcmp(artist, db->artists[i]->name) == 0)
        {
            ptr = db->artists[i];
            found = 1;
            break;
        }
        else
        {
            found = 0;
        }
    }
    if (found == 0)
    {
        return -1;
    }
}
