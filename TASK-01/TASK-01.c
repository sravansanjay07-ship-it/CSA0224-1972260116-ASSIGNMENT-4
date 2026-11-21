#include <stdio.h>
#include <string.h>

struct Date
{
    int day, month, year;
};

struct BP
{
    int systolic;
    int diastolic;
};

struct Patient
{
    char name[50];
    int age;
    char phone[16];
    struct BP bp;
    struct Date visitDate;
};

void addPatient(struct Patient *p, char name[],
                int age, char phone[],
                int sys, int dia, struct Date d)
{
    strcpy(p->name, name);
    p->age = age;
    strcpy(p->phone, phone);
    p->bp.systolic = sys;
    p->bp.diastolic = dia;
    p->visitDate = d;
}

int main()
{
    struct Patient p;
    struct Date d = {21, 11, 2026};

    addPatient(&p, "Arun", 25, "9876543210",
               120, 80, d);

    printf("Patient Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Phone: %s\n", p.phone);
    printf("Blood Pressure: %d/%d\n",
           p.bp.systolic, p.bp.diastolic);
    printf("Visit Date: %02d/%02d/%04d\n",
           p.visitDate.day,
           p.visitDate.month,
           p.visitDate.year);

    return 0;
}
