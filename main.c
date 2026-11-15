#include <stdio.h>
#include <stdlib.h>
#include "musicdb.h"

int main()
{
    int idLastFour = 6011;
    // calculate a, b, etc rest of stuff in the requirements
    int a = (idLastFour / 10) % 10;
    int b = (idLastFour % 10);
    int S = (a + 2 * b) % 4;
    int T = b % 5;
    int D = a % 5;
    int L = (a + b) % 4;
    // displays
    printf("ENEB340 REPORT\n");
    printf("card: L=%d D=%d T=%d S=%d\n", L, D, T, S);

    printf("[A] sizeof(Song)=%d\n", (int)sizeof(Song));

    MusicDB *db = db_create();
    db_load(db, "data");
    printf("[B] songs=%d artists=%d\n", (int)db_song_count(db), (int)db_artist_count(db));

    Song *firstSong = db_get(db, 0);
    printf("[B] song[0]: %s | %s | %d | %.2f | %d\n", firstSong->title, firstSong->artist->name, firstSong->year, firstSong->rating, (int)firstSong->num_rated);

    Artist *topArtist = db_top_artist(db);
    printf("[B] top_artist: %s (%d songs)\n", topArtist->name, (int)topArtist->n_songs);

    db_push(db, "Exam Song 6011", "Exam Artist 6011", 4.10, 1985, 1250000);
    printf("[C] push1 -> songs=%d artists=%d\n", (int)db_song_count(db), (int)db_artist_count(db));

    db_push(db, "Exam Song 6011 (Reprise)", "The Beatles", 3.70, 1985, 1250000);
    printf("[C] push2 -> songs=%d artists=%d\n", (int)db_song_count(db), (int)db_artist_count(db));

    printf("[C] beatles_songs=%d\n", (int)db_get(db, db_song_count(db) - 1)->artist->n_songs);

    const Song *bestSong = NULL;
    int decadeCount = db_count_decade(db, 1960 + 10 * D, &bestSong);
    printf("[D] Q1 decade=%d count=%d best_id=%d best_title=%s\n", 1960 + 10 * D, decadeCount, bestSong->id, bestSong->title);
    int matchCount = 0;
    int firstMatchId = 0;
    int lastMatchId = 0;
    for (int i = 0; i < (int)db_song_count(db); i++)
    {
        Song *song = db_get(db, i);
        if (song->rating * 100 + 0.5 >= 390 && (int)song->num_rated >= 1100000)
        {
            if (matchCount == 0)
            {
                firstMatchId = song->id;
            }
            lastMatchId = song->id;

            matchCount++;
        }
    }
    printf("[D] Q2 rating>=3.90 rated>=1100000 count=%d first_id=%d last_id=%d\n", matchCount, firstMatchId, lastMatchId);

    db_sort(db, S);

    printf("[D] sort card %d top5 ids: %d %d %d %d %d\n", S, db_get(db, 0)->id, db_get(db, 1)->id, db_get(db, 2)->id, db_get(db, 3)->id, db_get(db, 4)->id);
    db_disp(db, stdout, 3);

    db_destroy(db);
    return 0;
}