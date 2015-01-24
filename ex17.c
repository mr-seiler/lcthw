#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// coudl also use "#define" here
enum { MAX_DATA=512, MAX_ROWS=100 };

/* Utility function for exiting on error */
void die(const char *message)
{
    // if the external error code is set, print it w/ our message
    if (errno)
    {
        perror(message);
    }
    else // otherwise just print our message
    {
        printf("ERROR: %s\n", message);
    }

    // terminate the program w/ non-zero code
    exit(1);
}

/* Address struct
 * Because this is supposed to model a database system,
 * it makes sense for name and email to be fixed-length.
 */
struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

/* Address printer */
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}


/* Database struct
 * Not strictly necessary for this example, but if you wanted to have
 * other "tables" besides just addresses in the database then this struct
 * would hold each one.
 */
struct Database {
    struct Address rows[MAX_ROWS];
};

/* Database file handle and pointer to db in memory
 */
struct Connection {
    FILE *file;
    struct Database *db;
};

/* Assuming a connection's file has already been fopen'd,
 * will populate the connection's database from the file contents.
 */
void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to load database");
}

/* Given a filename string and mode spec,
 * returns a pointer to a connection struct */
struct Connection *Database_open(const char *filename, char mode)
{
    // allocate connection
    struct Connection *conn = malloc(sizeof(struct Connection));
    // NULL evaluates to int 0, so if malloc failed we can check w/ "!thing"
    if (!conn) die("Memory allocation error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die ("Memory allocation error");

    if (mode == 'c')
    {
        conn->file = fopen(filename, "w");
    }
    else
    {
        conn->file = fopen(filename, "r+");

        if (conn->file)
        {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Failed to open the file");

    return conn;
}

/* Given a pointer to a connection,
 * close the connection's file handle (if it is open)
 * and clear it's database from memory (if it exists)
 * before freeing the connection struct itself.
 */
void Database_close(struct Connection *conn)
{
    if (conn)
    {
        if (conn->file)
        {
            fclose(conn->file);
        }
        if (conn->db)
        {
            free(conn->db);
        }
        free(conn);
    }
}

/* Writes the in-memory database struct to the databse file and
 * flushes the file write buffer (I think).
 */
void Database_write(struct Connection *conn)
{
    // move the file pointer back to the beginning (so we overwrite, I presume)
    // Don't have to worry about partial overwrites b/c our db is fixed-size!
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to write databse to file");

    rc = fflush(conn->file);
    if (rc == -1) die("Could not flush database");
}

/* Sets each row in the database to a new Address struct
 * with a sequential id and the "set" attribute false.
 */
void Database_create(struct Connection *conn)
{
    int i;
    for (i = 0; i < MAX_ROWS; i += 1)
    {
        // create struct prototype
        struct Address addr = {.id = i, .set = 0};
        // put the struct in a database row
        conn->db->rows[i] = addr;
    }
}

/* Sets the contents of the specified address to the given name and email */
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    // initialize a pointer to an address struct located at offset `id`
    // of the rows array in the db struct in the conn struct.  Savvy?
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first");

    // flag this address entry as having contents
    addr->set = 1;

    // FIXME: THERE IS A BUG HERE
    // (I think I see it - the first arg should be a pointer but -> gives us the contents?)
    // WRONG - he's talking about manually null-terminating the last byte.  pleh.
    char *res = strncpy(addr->name, name, MAX_DATA);
    if (!res) die("Name copy failed");
    // see above.  and below.
    addr->name[MAX_DATA - 1] = '\0';

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res) die("Email copy failed");
    // make sure that the strings are ALWAYS null-terminated, even if we pass
    // in a string longer than MAX_DATA.  ( Does cause truncation ).
    addr->email[MAX_DATA - 1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set)
    {
        Address_print(addr);
    }
    else
    {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    // this looks familiar, like we did exactly this earlier somewhere
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i += 1)
    {
        struct Address *cadre = &db->rows[i];

        if (cadre->set)
        {
            Address_print(cadre);
        }
    }
}

/* main method (doi) */
int main(int argc, char *argv[])
{
    if (argc < 3) die("USAGE: ex7 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);

    int id = 0;

    // atoi converts the first part of the string to an int
    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("WOA not that many records yo");

    switch (action)
    {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;
        case 'g':
            if (argc != 4) die("Need an ID to get");
            Database_get(conn, id);
            break;
        case 's':
            if (argc != 6) die("Need id, name, email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        case 'd':
            if (argc != 4) die("Need an ID to delete");
            Database_delete(conn, id);
            Database_write(conn);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}

