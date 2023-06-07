#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

FILE *fle,*fle2;
char date[20];
char casetype[1];

struct Patient {
    int id;
    char name[20];
    char address[50];
    int age;
    char sex[10];
    char diseaseDesc[100];
    int docno;
    char specialist[20];
};

struct Test{
    char testname[50];
    double testmoney;
    double testdeposit;
    double moretopay;
};

void specialist_list(){
    printf("\nSpecialists : \n");
    printf("1. General Physician\n");
	printf("2. E.N.T\n");
	printf("3. Cardiologist\n");
	printf("4. Dermatologist\n");
	printf("5. Gastroenterologist\n");
	printf("6. Pediatrician\n");
	printf("7. EYE Specialist\n");
	printf("8. Nephrologist\n");
	printf("9. General Surgeon\n");
	printf("10. Accupuncturist\n");
}

void test_list(){    
	printf("ADDING SERVICES :\n");
	printf("1. X-Ray - ");
	printf("Rs. 300.00\n");
	printf("2. Ultra-sound - ");
	printf("Rs. 500.00\n");
	printf("3. C.T.Scan - ");
	printf("Rs.1800.00\n");
	printf("4. TC,DC,HB - ");
	printf("Rs.  90.00\n");
	printf("5. Urine R/E - ");
	printf("Rs.  80.00\n");
	printf("6. Blood C/S - ");
	printf("Rs. 250.00\n");
	printf("7. Biliribin D/T - ");
	printf("Rs. 200.00\n");
	printf("8. Stool Test - ");
	printf("Rs.  60.00\n");
	printf("9. Bed Charge - ");
	printf("Rs. 150.00\n");
	printf("10. Sugar Test - ");
	printf("Rs. 400.00\n");
}


//----------------------------------------------------  CASE 4  --------------------------------------------------------
void deleteRecord() {
    int lineNumber;
    char line[100], date[20], casetype[20];
    FILE* originalFile, * tempFile;

    originalFile = fopen("PatientRec.txt", "r");
    if (originalFile == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create a temporary file.\n");
        fclose(originalFile);
        return;
    }

    printf("Enter the line number of the record to delete: ");
    scanf("%d", &lineNumber);

    int currentLine = 1;
    int recordDeleted = 0;

    while (fgets(line, sizeof(line), originalFile) != NULL) {
        if (currentLine != lineNumber) {
            fputs(line, tempFile);
        } else {
            struct Patient patient;
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
                &patient.id, date, casetype, patient.name, patient.address,
                &patient.age, patient.sex, patient.diseaseDesc,&patient.docno,patient.specialist);


            printf("\nPatient Details to delete:\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist : %s\n", patient.specialist);

            char confirmation;
            printf("Confirm deletion (Y/N): ");
            scanf(" %c", &confirmation);

            if (confirmation == 'Y' || confirmation == 'y') {
                recordDeleted = 1;
                fputc('\n', tempFile);
            }
            else {
                fputs(line, tempFile);
            }
        }

        currentLine++;
    }

    fclose(originalFile);
    fclose(tempFile);

    if (recordDeleted) {
        originalFile = fopen("PatientRec.txt", "w");
        tempFile = fopen("temp.txt", "r");

        if (originalFile == NULL || tempFile == NULL) {
            printf("Failed to open the file.\n");
            return;
        }

        char c;
        while ((c = fgetc(tempFile)) != EOF) {
            fputc(c, originalFile);
        }

        fclose(originalFile);
        fclose(tempFile);
        remove("temp.txt");
        printf("Record erased successfully.\n");
    } else {
        remove("temp.txt");
        printf("No record was found.\n");
    }
}


//----------------------------------------------------  CASE 3  --------------------------------------------------------
void displaybill(int sno) {
    FILE* filebil = fopen("Patientamount.txt", "r");
    if (filebil == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char linebil[100];
    int lineNumberbil = 1;

    while (fgets(linebil, sizeof(linebil), filebil) != NULL) {
        if (linebil[0] == '\n') {
            continue;
        }
        

        struct Patient patient;
        struct Test test;
        sscanf(linebil, "%d,%[^,],%lf,%lf,%lf",&patient.id, test.testname, &test.testmoney, &test.testdeposit, &test.moretopay);

        if (patient.id == sno){
        printf("All test charges name : %s\n", test.testname);
        printf("All test charges: %.lf\n", test.testmoney);
        printf("Total money patient deposited: %.lf\n\n", test.testdeposit);

        if(test.moretopay > 0){
            printf("Remaning Money to pay : %lf\n",test.moretopay);}
        else{
            printf("Money to be returned to the paitent : %lf\n",-test.moretopay);}
    
        }

        lineNumberbil++;
    }

    fclose(filebil);
}



void displayRecordsOnID() {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];
    int checkid;
    int lineNumber = 1;
    printf("Enter Specific ID of records : ");
    scanf("%d",&checkid);

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }

        struct Patient patient;
         sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
            &patient.id, date, casetype, patient.name, patient.address,
            &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

        int sno = patient.id;

        if (patient.id == checkid) {
            printf("\nPatient Details :\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist : %s\n", patient.specialist);
            
            printf("\nPress 'q' to quit or 'b' to display the BILL details: ");
            char input;
            scanf(" %c", &input);
            printf("\n");

            if (input == 'q'){
                    fclose(file);
                    return;
                }

            else if (input == 'b') {
                displaybill(sno);
                printf("\n\nPress 'q' to quit : ");
                scanf(" %c", &input);
                printf("\n");
                if (input == 'q'){
                    fclose(file);
                    return;
                }
            }
        }

        lineNumber++;
    }

    fclose(file);
    printf("No more records to display.\n");
}



void displayRecordsOnDate() {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];
    char checkdate[20];
    int lineNumber = 1;
    printf("Enter Specific date of records : ");
    scanf("%s",checkdate);

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }

        struct Patient patient;
         sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
            &patient.id, date, casetype, patient.name, patient.address,
            &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

        int sno = patient.id;

        if (strcmp(date, checkdate) == 0) {
            printf("\nPatient Details :\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist : %s\n", patient.specialist);

            printf("\nPress 'q' to quit or 'b' to show the BILL or AnyLetter' to display the next record: ");
            char input;
            scanf(" %c", &input);
            printf("\n");
            if (input == 'q'){
                    fclose(file);
                    return;
                }

            else if (input == 'b') {
                displaybill(sno);
                printf("\n\nPress 'q' to quit or AnyLetter' to display the next record : ");
                scanf(" %c", &input);
                printf("\n");
                if (input == 'q'){
                    fclose(file);
                    return;
                }
            }
        }

        lineNumber++;
    }

    fclose(file);
    printf("No more records to display.\n");
}



void displayRecordsEmergency() {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];
    int lineNumber = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }

        struct Patient patient;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
            &patient.id, date, casetype, patient.name, patient.address,
            &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

        int sno = patient.id;

        if (strcmp(casetype, "e") == 0) {
            printf("\nPatient Details :\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist : %s\n", patient.specialist);

            printf("\nPress 'q' to quit or 'b' to show the BILL or AnyLetter' to display the next record: ");
            char input;
            scanf(" %c", &input);
            printf("\n");

            if (input == 'q'){
                    fclose(file);
                    return;
                }

            else if (input == 'b') {
                displaybill(sno);
                printf("\n\nPress 'q' to quit or AnyLetter' to display the next record : ");
                scanf(" %c", &input);
                printf("\n");
                if (input == 'q'){
                    fclose(file);
                    return;
                }
            }
        }

        lineNumber++;
    }

    fclose(file);
    printf("No more Emergency records to display.\n");
}



void displayRecordsOPD() {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];
    int lineNumber = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }

        struct Patient patient;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
            &patient.id, date, casetype, patient.name, patient.address,
            &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

        int sno = patient.id;

        if (strcmp(casetype, "o") == 0) {
            printf("\nPatient Details :\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist : %s\n", patient.specialist);

            printf("\nPress 'q' to quit or 'b' to show the BILL or AnyLetter' to display the next record: ");
            char input;
            scanf(" %c", &input);
            printf("\n");

            if (input == 'q'){
                    fclose(file);
                    return;
                }

            else if (input == 'b') {
                displaybill(sno);
                printf("\n\nPress 'q' to quit or AnyLetter' to display the next record : ");
                scanf(" %c", &input);
                printf("\n");
                if (input == 'q'){
                    fclose(file);
                    return;
                }
            }
        }

        lineNumber++;
    }

    fclose(file);
    printf("No more OPD records to display.\n");
}



void displayRecordsNumericalOrder() {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];
    int lineNumber = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;  
        }

        struct Patient patient;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
            &patient.id, date, casetype, patient.name, patient.address,
            &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

        int sno = patient.id;

        printf("\nPatient Details:\n");
        printf("ID: %d\n", patient.id);
        printf("Date: %s\n", date);
        printf("Case Type: %s\n", casetype);
        printf("Name: %s\n", patient.name);
        printf("Address: %s\n", patient.address);
        printf("Age: %d\n", patient.age);
        printf("Sex: %s\n", patient.sex);
        printf("Disease Description: %s\n", patient.diseaseDesc);
        printf("Ref. Specialist no: %d\n", patient.docno);
        printf("Specialist : %s\n", patient.specialist);

            printf("\nPress 'q' to quit or 'b' to show the BILL or AnyLetter' to display the next record: ");
            char input;
            scanf(" %c", &input);
            printf("\n");

            if (input == 'q'){
                    fclose(file);
                    return;
                }

            else if (input == 'b') {
                displaybill(sno);
                printf("\n\nPress 'q' to quit or AnyLetter' to display the next record : ");
                scanf(" %c", &input);
                printf("\n");
                if (input == 'q'){
                    fclose(file);
                    return;
                }
            }

        lineNumber++;
    }

    fclose(file);
    printf("No more records to display.\n");
}


//-----------------------------------------------------  CASE 2  ----------------------------------------------------------
void changeSpecialistByLineNumber(int lineNumber);
void searchRecordByLineNumber(int lineNumber) {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    int currentLine = 1;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLine == lineNumber) {
            struct Patient patient;
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
                &patient.id, date, casetype, patient.name, patient.address,
                &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

            printf("\nPatient Details:\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist : %s\n", patient.specialist);

            fclose(file);
            return;
        }

        currentLine++;
    }

    fclose(file);
    printf("No record found at line number %d.\n", lineNumber);
}



void appendDescription(int lineNumber) {

    FILE* originalFile = fopen("PatientRec.txt", "r");
    if (originalFile == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(originalFile);
        return;
    }

    int currentLine = 1;
    char line[100];

    while (fgets(line, sizeof(line), originalFile) != NULL) {
        if (currentLine == lineNumber) {
            struct Patient patient;
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
                &patient.id, date, casetype, patient.name, patient.address,
                &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

            printf("\nCurrent Patient Details:\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist: %s\n", patient.specialist);

            char newdesc[100];
            printf("\nEnter the new Description to be appended: ");
            scanf(" %[^\n]", newdesc); 
            strcat(patient.diseaseDesc, " + ");
            strcat(patient.diseaseDesc, newdesc);

            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%s,%s,%d,%s\n",
                    patient.id, date, casetype, patient.name, patient.address,
                    patient.age, patient.sex, patient.diseaseDesc, patient.docno, patient.specialist);

            printf("Description updated successfully.\n");
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentLine++;
    }

    fclose(originalFile);
    fclose(tempFile);

    if (currentLine <= lineNumber) {
        printf("No record found at line number %d.\n", lineNumber);
        remove("temp.txt");
    } else {
        originalFile = fopen("PatientRec.txt", "w");
        tempFile = fopen("temp.txt", "r");

        if (originalFile == NULL || tempFile == NULL) {
            printf("Failed to open the file.\n");
            return;
        }

        int c;
        while ((c = fgetc(tempFile)) != EOF) {
            fputc(c, originalFile);
        }

        fclose(originalFile);
        fclose(tempFile);
        remove("temp.txt");
        printf("Record updated successfully.\n");
    }
}



void Pharmacybill(int lineNumber) {
    FILE* originalFile = fopen("Patientamount.txt", "r");
    if (originalFile == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* originalFile2 = fopen("PatientRec.txt", "r");
    if (originalFile2 == NULL) {
        printf("Failed to open the file.\n");
        fclose(originalFile);
        return;
    }

    FILE* tempFile = fopen("temp2.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create a temporary file.\n");
        fclose(originalFile);
        fclose(originalFile2);
        return;
    }

    int currentLine = 1;
    int currentLine2 = 1;
    char line[500];
    char line2[500];
   

    while (fgets(line2, sizeof(line2), originalFile2) != NULL) {
        if (currentLine2 == lineNumber) {
            struct Patient patient;
            sscanf(line2, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
                &patient.id, date, casetype, patient.name, patient.address,
                &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

            printf("\nCurrent Patient Details:\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist: %s\n\n", patient.specialist);
        }
        currentLine2++;
    }
    fclose(originalFile2);

    while (fgets(line, sizeof(line), originalFile) != NULL) {
        struct Patient patient;
        struct Test test;
        sscanf(line, "%d,%[^,],%lf,%lf,%lf",&patient.id, test.testname, &test.testmoney, &test.testdeposit, &test.moretopay);

        if (currentLine == lineNumber) {
            printf("All test charges name : %s\n", test.testname);
            printf("All test charges: %.lf\n\n", test.testmoney);


            test_list();

            char newtest[100];
            int testno;
            double money;

            printf("Enter the new test number to be appended: ");
            scanf("%d", &testno);

            switch (testno) {
                case 1: strcpy(newtest, "X-Ray"); money = 300; break;
                case 2: strcpy(newtest, "Ultra-sound"); money = 500; break;
                case 3: strcpy(newtest, "C.T.Scan"); money = 1800; break;
                case 4: strcpy(newtest, "TC,DC,HB"); money = 90; break;
                case 5: strcpy(newtest, "Urine R/E"); money = 80; break;
                case 6: strcpy(newtest, "Blood C/S"); money = 250; break;
                case 7: strcpy(newtest, "Bilirubin D/T"); money = 200; break;
                case 8: strcpy(newtest, "Stool Test"); money = 60; break;
                case 9: strcpy(newtest, "Bed Charge"); money = 150; break;
                case 10: strcpy(newtest, "Sugar Test"); money = 400; break;
                default: break;
            }

            strcat(test.testname, " + ");
            strcat(test.testname, newtest);

            test.testmoney += money;

            fprintf(tempFile, "%d,%s,%lf,%lf,%lf\n",patient.id, test.testname, test.testmoney,test.testdeposit, test.moretopay);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentLine++;
    }

    fclose(originalFile);
    fclose(tempFile);

    if (currentLine2 <= lineNumber) {
        printf("No record found at line number %d.\n", lineNumber);
        remove("temp2.txt");
    } else {
        originalFile = fopen("Patientamount.txt", "w");
        tempFile = fopen("temp2.txt", "r");

        if (originalFile == NULL || tempFile == NULL) {
            printf("Failed to open the file.\n");
            return;
        }

        int c;
        while ((c = fgetc(tempFile)) != EOF) {
            fputc(c, originalFile);
        }

        fclose(originalFile);
        fclose(tempFile);
        remove("temp2.txt");
        printf("Record updated successfully.\n");
    }
}



void depositbill(int lineNumber) {
    FILE* originalFile = fopen("Patientamount.txt", "r");
    if (originalFile == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* tempFile = fopen("temp2.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create a temporary file.\n");
        fclose(originalFile);
        return;
    }

    int currentLine = 1;
    char line[500];


    while (fgets(line, sizeof(line), originalFile) != NULL) {
        struct Patient patient;
        struct Test test;
        sscanf(line, "%d,%[^,],%lf,%lf,%lf",&patient.id, test.testname, &test.testmoney, &test.testdeposit, &test.moretopay);



        if (currentLine == lineNumber) {
            printf("All test charges name : %s\n", test.testname);
            printf("All test charges: %.lf\n", test.testmoney);
            printf("Total money patient deposited: %.lf\n\n", test.testdeposit);

            double testdep;
            test.moretopay = test.testmoney - test.testdeposit;

            if(test.moretopay > 0){
                printf("Remaning Money to pay : %lf\n",test.moretopay);
                printf("Enter deposit money : ");                
                scanf("%lf", &testdep);
                test.testdeposit = test.testdeposit + testdep;
                test.moretopay = test.testmoney - test.testdeposit;
            }
            else{
                printf("Money to be returned to the paitent : %lf\n",-test.moretopay);

            }
                
            fprintf(tempFile, "%d,%s,%lf,%lf,%lf\n",patient.id, test.testname, test.testmoney, test.testdeposit, test.moretopay);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentLine++;
    }

    fclose(originalFile);
    fclose(tempFile);

    if (currentLine <= lineNumber) {
        printf("No record found at line number %d.\n", lineNumber);
        remove("temp2.txt");
    } else {
        originalFile = fopen("Patientamount.txt", "w");
        tempFile = fopen("temp2.txt", "r");

        if (originalFile == NULL || tempFile == NULL) {
            printf("Failed to open the file.\n");
            return;
        }

        int c;
        while ((c = fgetc(tempFile)) != EOF) {
            fputc(c, originalFile);
        }

        fclose(originalFile);
        fclose(tempFile);
        remove("temp2.txt");
        printf("Record updated successfully.\n");
    }
}



void searchRecordsNum() {
    FILE* file = fopen("PatientRec.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];

    printf("Enter the number of the record to Edit: ");
    int lineNumber;
    scanf("%d", &lineNumber);

    int currentLine = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLine == lineNumber) {
            struct Patient patient;
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
                &patient.id, date, casetype, patient.name, patient.address,
                &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);


            printf("\nEnter the corresponding number:\n");
            printf("1. Add more Disease Description\n");
            printf("2. Change Specialist\n");
            printf("3. Pharmacy bill\n");
            printf("4. Money deposit\n");
            printf("5. Return to the main menu\n\n");
            int searchcho;
            scanf("%d", &searchcho);

            switch (searchcho) {
                case 1:
                    appendDescription(lineNumber);
                    break;
                case 2:
                    changeSpecialistByLineNumber(lineNumber);
                    break;
                case 3:
                    Pharmacybill(lineNumber);
                    break;
                case 4:
                    depositbill(lineNumber);
                    break;
                default:
                    break;
            }
            break;
        }

        currentLine++;
    }

    fclose(file);

    if (currentLine > lineNumber) {
        printf("No record found at line number %d.\n", lineNumber);
    }
}



void changeSpecialistByLineNumber(int lineNumber) {
    FILE* originalFile = fopen("PatientRec.txt", "r");
    if (originalFile == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(originalFile);
        return;
    }

    int currentLine = 1;
    char line[100];

    while (fgets(line, sizeof(line), originalFile) != NULL) {
        if (currentLine == lineNumber) {
            struct Patient patient;
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,]",
                &patient.id, date, casetype, patient.name, patient.address,
                &patient.age, patient.sex, patient.diseaseDesc, &patient.docno, patient.specialist);

            printf("\nCurrent Patient Details:\n");
            printf("ID: %d\n", patient.id);
            printf("Date: %s\n", date);
            printf("Case Type: %s\n", casetype);
            printf("Name: %s\n", patient.name);
            printf("Address: %s\n", patient.address);
            printf("Age: %d\n", patient.age);
            printf("Sex: %s\n", patient.sex);
            printf("Disease Description: %s\n", patient.diseaseDesc);
            printf("Ref. Specialist no: %d\n", patient.docno);
            printf("Specialist: %s\n", patient.specialist);

            specialist_list();

            printf("\nEnter the new specialist number: ");
            scanf("%d", &patient.docno);

            switch (patient.docno) {
                case 1: strcpy(patient.specialist, "General Physician"); break;
                case 2: strcpy(patient.specialist, "E.N.T"); break;
                case 3: strcpy(patient.specialist, "Cardiologist"); break;
                case 4: strcpy(patient.specialist, "Dermatologist"); break;
                case 5: strcpy(patient.specialist, "Gastroenterologist"); break;
                case 6: strcpy(patient.specialist, "Pediatrician"); break;
                case 7: strcpy(patient.specialist, "EYE Specialist"); break;
                case 8: strcpy(patient.specialist, "Nephrologist"); break;
                case 9: strcpy(patient.specialist, "General Surgeon"); break;
                case 10: strcpy(patient.specialist, "Accupuncturist"); break;
                default: strcpy(patient.specialist, "Unknown"); break;
            }

            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%s,%s,%d,%s\n",
                    patient.id, date, casetype, patient.name, patient.address,
                    patient.age, patient.sex, patient.diseaseDesc, patient.docno, patient.specialist);

            printf("Specialist updated successfully.\n");
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentLine++;
    }

    fclose(originalFile);
    fclose(tempFile);

    if (currentLine <= lineNumber) {
        printf("No record found at line number %d.\n", lineNumber);
    } else {
        originalFile = fopen("PatientRec.txt", "w");
        tempFile = fopen("temp.txt", "r");

        if (originalFile == NULL || tempFile == NULL) {
            printf("Failed to open the file.\n");
            return;
        }

        char c;
        while ((c = fgetc(tempFile)) != EOF) {
            fputc(c, originalFile);
        }

        fclose(originalFile);
        fclose(tempFile);
        remove("temp.txt");
        printf("Record updated successfully.\n");
    }
}


//-----------------------------------------------------  CASE 1  ----------------------------------------------------------
void newrecord(int max_row) {

    struct Patient patient;
    struct Test test;

    specialist_list();

    printf("\n\nRecord of patient no: %d", max_row);
    printf("\nName: "); scanf(" %[^\n]", patient.name);
    printf("Address: "); scanf(" %[^\n]", patient.address);
    printf("Age: "); scanf("%d", &patient.age);
    printf("Sex (m/f): "); scanf(" %[^\n]", &patient.sex);
    printf("Disease Descrp: "); scanf(" %[^\n]", patient.diseaseDesc);
    printf("Reff. Specialist no: "); scanf("%d", &patient.docno);

    switch(patient.docno){
        
        case 1: {
            strcpy(patient.specialist, "General Physician");
            break;
        }
        case 2: {
            strcpy(patient.specialist, "E.N.T");
            break;
        }
        case 3: {
            strcpy(patient.specialist, "Cardiologist");
            break;
        }
        case 4: {
            strcpy(patient.specialist, "Dermatologist");
            break;
        }
        case 5: {
            strcpy(patient.specialist, "Gastroenterologist");
            break;
        }
        case 6: {
            strcpy(patient.specialist, "Pediatrician");
            break;
        }
        case 7: {
            strcpy(patient.specialist, "EYE Specialist");
            break;
        }
        case 8: {
            strcpy(patient.specialist, "Nephrologist");
            break;
        }
        default: {
            strcpy(patient.specialist, "Unknown");
            break;
        }


    }

    printf("Specialist : %s\n",patient.specialist);

    fprintf(fle, "%d,%s,%s,%s,%s,%d,%s,%s,%d,%s\n", max_row, date, casetype,
        patient.name, patient.address, patient.age, patient.sex,
        patient.diseaseDesc, patient.docno, patient.specialist);
    fflush(fle);

    

    if(strcmp(casetype, "o") == 0){
        strcpy(test.testname, "OPD charge");
        test.testmoney = 200.00;
        test.testdeposit = 0.00;
        test.moretopay = test.testmoney - test.testdeposit;
        fprintf(fle2, "%d,%s,%f,%f,%f\n", max_row, test.testname, test.testmoney, test.testdeposit, test.moretopay);
        fflush(fle2);
    }
    else{
        strcpy(test.testname, "Emergency charge");
        test.testmoney = 300.00;
        test.testdeposit = 0.00;
        test.moretopay = test.testmoney - test.testdeposit;
        fprintf(fle2, "%d,%s,%f,%f,%f\n", max_row, test.testname, test.testmoney, test.testdeposit, test.moretopay);
        fflush(fle2);
    }

}



void mainchoose(int max_row) {
    int maincho,searchcho;
    printf("\n\nJEENA CARE HOSPITAL MANAGMENT SYSTEM");
    printf("\n\nEnter the corresponding number:\n");
    printf("1. Add new patient record\n");
    printf("2. Edit patient record\n");
    printf("3. Know the records of patients\n");
    printf("4. Delete the records\n");
    printf("5. Exit from the program\n\n");

    scanf("%d", &maincho);

    switch (maincho) {
        case 1:
            printf("Enter 'o' - OPD case or 'e' - Emergency case: ");
            scanf("%s", casetype);
            newrecord(max_row);
            break;
        case 2:
            searchRecordsNum();
            break;
        case 3:
        	printf("Enter the corresponding no:\n");
            printf("1. Records of All patients in order\n");
            printf("2. Records of O.P.D. patients\n");
            printf("3. Records of Emergency patients\n");
            printf("4. Records in paricular ID\n");
            printf("5. Records in paricular date\n");
            printf("6. Return to main menu\n\n");
            scanf("%d", &searchcho);
            switch(searchcho){
                case 1:
                    displayRecordsNumericalOrder();
                    break;
                case 2:
                    displayRecordsOPD();
                    break;
                case 3:
                    displayRecordsEmergency();
                    break;
                case 4:
                    displayRecordsOnID();
                    break;
                case 5:
                    displayRecordsOnDate();
                    break;
                default:
                    break;
            }
            break;

        case 4:
            deleteRecord();
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice\n");
            break;
    }
}



int main() {
    char line[100];
    int row = 0;

    printf("Enter the date ( DD-MM-YYYY ): ");
    scanf("%s", date);

    fle = fopen("PatientRec.txt", "a+");
    if (fle == NULL) {
        printf("Failed to open the file.\n");
        return 1;}
    fle2 = fopen("Patientamount.txt", "a+");
    if (fle == NULL) {
        printf("Failed to open the file.\n");
        return 1;}

    while (1) {
        while (fgets(line, sizeof(line), fle) != NULL) {
        row++;}
        int max_row = row + 1;
        mainchoose(max_row);}

    fclose(fle);
    return 0;
}
