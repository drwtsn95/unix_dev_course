#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum ERROR_CODE {
	BAD_ARGS,
	SAME_FILE_ERROR,
	INFILE_OPEN_ERROR,
	INFILE_CLOSE_ERROR,
	OUTFILE_OPEN_ERROR,
	READ_WRITE_ERROR,
	OUTFILE_CLOSE_ERROR,
	OUTFILE_FSEEK_ERROR,
	OUTFILE_FTELL_ERROR,
	CHECKSUM_ERROR,
	INFILE_REMOVE_ERROR,
	OUTFILE_REMOVE_ERROR
};

int main(int argc, char** argv) {
	FILE *infile, *outfile;
	char c;
	int infile_len = 0, outfile_len = 0;
	if (argc != 3) {
		fprintf(stderr, "Usage:\n");
    	fprintf(stderr, "%s infile outfile\n", argv[0]);
		return BAD_ARGS;
	}

	if (!strcmp(argv[1], argv[2])) {
		fprintf(stderr, "Files must be different. It's nonsense!\n");
		return SAME_FILE_ERROR;
	}

	infile = fopen(argv[1], "r");
	if (infile == NULL) {
		fprintf(stderr, "Failed to open infile\n");
		return INFILE_OPEN_ERROR;
	}
	
	outfile = fopen(argv[2], "w");
	if (outfile == NULL) {
		fprintf(stderr, "Failed to open outfile\n");
		return OUTFILE_OPEN_ERROR;
	}


	while ((c = fgetc(infile)) != EOF) {
		infile_len++;
        fputc(c, outfile);
        fflush(outfile); //Ну вот такой костылик подъехал, но условий на оптимальность программы не было.
    }

    if (fclose(infile) != 0) {
        fprintf(stderr, "Failed to close infile\n");
        return INFILE_CLOSE_ERROR;
    }

    if (errno != 0) {
    	fprintf(stderr, "Something went wrong during copying\n");
    	if (fclose(outfile) != 0) {
        	fprintf(stderr, "Failed to close outfile\n");
        	return OUTFILE_CLOSE_ERROR;
    	}
    	if (remove(argv[2]) != 0) {
        	fprintf(stderr, "Failed to remove outfile\n");
        	return OUTFILE_REMOVE_ERROR;
    	}
    	return READ_WRITE_ERROR;
    }
    // Let's check simple checksum 

    if (fseek(outfile, 0, SEEK_END) != 0) {
        fprintf(stderr, "Failed to fseek outfile\n");
        return OUTFILE_FSEEK_ERROR;
    }

    if ((outfile_len = ftell(outfile)) == -1) {
    	fprintf(stderr, "Failed to call ftell on outfile\n");
    	return OUTFILE_FTELL_ERROR;
    }

    if (infile_len != outfile_len) {
        fprintf(stderr, "File sizes don't match\n");
        return CHECKSUM_ERROR;
    }

	if (fclose(outfile) != 0) {
        fprintf(stderr, "Failed to close outfile\n");
        return OUTFILE_CLOSE_ERROR;
    }

    if (remove(argv[1]) != 0) {
        fprintf(stderr, "Failed to remove infile\n");
        return INFILE_REMOVE_ERROR;
    }

    return 0;
}