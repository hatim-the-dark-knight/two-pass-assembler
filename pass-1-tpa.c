#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main () {

    FILE *inp_pgm_fp, *opcd_tbl_fp, *intermediate_fp, *sym_tbl_fp, *len_fp;

    char label[10], opcode[10], operand[10], op_code[10], hexacode[10];

    int start_address, loc_ctr, pgm_len;
    
    inp_pgm_fp = fopen ("input-pgm-p1.dat", "r");
    intermediate_fp = fopen ("output-intmdt-file-p1.dat", "w");
    sym_tbl_fp = fopen ("output-symb-tbl-p1.dat", "w");
    len_fp = fopen ("output-pgm-len-p1.dat", "w");

    fscanf (inp_pgm_fp, "%s\t%s\t%X", label, opcode, &start_address);
    if (strcmp (opcode, "START") == 0) {
        loc_ctr = start_address;
        fprintf (intermediate_fp, "-\t%s\t%s\t%X\n", label, opcode, start_address);
    }
    else {
        loc_ctr = 0x0;
        printf ("\nInvalid Entries detected!\n");
    }

    fscanf (inp_pgm_fp, "%s\t%s\t%s", label, opcode, operand);

    while (!feof (inp_pgm_fp)) {

        fprintf (intermediate_fp, "%X\t%s\t%s\t%s\n", loc_ctr, label, opcode, operand);

        if (strcmp (label, "-") != 0) {
            fprintf (sym_tbl_fp, "%s\t%X\n", label, loc_ctr);
        }

        opcd_tbl_fp = fopen ("input-opcode-table-p1.dat", "r");
        fscanf (opcd_tbl_fp, "%s\t%s", op_code, hexacode);

        while (!feof (opcd_tbl_fp)) {
            if (strcmp (opcode, op_code) == 0) {
                loc_ctr += 0x3;
                break;
            }
            fscanf (opcd_tbl_fp, "%s\t%s", op_code, hexacode);
        }
        fclose (opcd_tbl_fp);

        if (strcmp (opcode, "WORD") == 0) {
            loc_ctr += 0x3;
        }
        else if (strcmp (opcode, "RESW") == 0) {
            loc_ctr += (0x3*atoi(operand));
        }
        else if (strcmp (opcode, "RESB") == 0) {
            loc_ctr += atoi (operand);
        }
        else if (strcmp (opcode, "BYTE") == 0) {
            if (operand[0] == 'X') {
                loc_ctr += 0x1;
            }
            else {
                loc_ctr += (strlen (operand)-0x2);
            }
        }

        fscanf (inp_pgm_fp, "%s\t%s\t%s", label, opcode, operand);
    }

    if (strcmp (opcode, "END") == 0) {
        fprintf (intermediate_fp, "-\t-\t%s\t%s\n", opcode, operand);
        pgm_len = loc_ctr - start_address;
        fprintf (len_fp, "%X\n", pgm_len);
    }

    fclose (inp_pgm_fp);
    fclose (intermediate_fp);
    fclose (sym_tbl_fp);
    fclose (len_fp);

}
