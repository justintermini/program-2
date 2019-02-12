/******************************************************************************



*******************************************************************************/
#include <stdio.h>

    /* Function headers */
    /*******************/
char  get_company_name ( char[] );
int   num_of_employees ( int );
float overtime_calc ( float, float );
float gross_pay_calc ( float, float, float );
void  safer_gets ( char[], int );
float tax_calc ( float );
float net_calc ( float, float );

int main()
{
    /* Variable Declarations */
    /************************/
    
    char     c, company_name[80], employee_name[80];
    int      x, num_employees;
    float    rate[10], hours[10], overtime[10], gross_pay[10], federal_tax[10], net_pay[10], total_gross = 0, total_tax = 0, total_net = 0;
    
    
    printf( "Welcome to the TERMINI Payroll Calculator\n\n" );
    
    get_company_name ( company_name ); /* Function call to get company name */
    
    printf ( "\nEnter the number of employees (1-10): " ); /* Prompts user for number of employees */
    scanf ( "%i", &num_employees );
    while ( (c = getchar() != '\n' ) && c != EOF); /* Buffer clearing statement */
    
    num_of_employees ( num_employees ); /* Function call to get number of employees */
    
    
    
    for ( x = 0; x < num_employees; x++ ) /* Loop which runs once for each employee */
    {
        
        
        printf ( "\nEnter name for employee %i: ", x + 1 ); /* Prompts user for employee name */
        safer_gets ( employee_name, 80 );
         
        
        do /* Hours worked trap loop */
        {
            printf ( "Enter the number for hours employee %i worked: ", x + 1 ); /* Prompts user for hours worked */ 
            scanf ( "%f", &hours[x] );
            while ( (c = getchar() != '\n') && c != EOF); /* clear input buffer */
            
            if ( hours[x] < 0 ) /* Trap loop to make sure hours worked is correct */
            printf ( "*** Invalid number of hours entered. Try again. ***\n\n");
        } while ( hours[x] < 0 ); 
        
        do /* Hourly rate entry loop */
        {
            printf ( "Enter the hourly rate of employee %i: ", x + 1 ); /* Prompts user for hourly rate */ 
            scanf ( "%f", &rate[x] );
            while ( (c = getchar() != '\n') && c != EOF); /* clear input buffer */
            
            if ( rate[x] < 0 ) /* Trap loop to make sure hourly rate is correct */
            printf ( "*** Invalid rate entered. Try again. ***\n\n");
    
        
        } while ( rate[x] < 0 ); 
        
    }
    
    
    /* Program Output Section Below */ 
    /*******************************/
    
    printf ( "\n\n\t\tPayroll Report\n" );
    printf ( "\t\t%s\n", company_name );
    printf ( "\t\t--------------\n\n");
   
    for ( x = 0; x < num_employees; x++ ) /* This loop runs once for each employee */ 
    {
        
        if ( hours[x] > 40 ) /* Determines if overtime calc function should be called */
            overtime[x] = overtime_calc ( hours[x], rate[x]);
        else 
            overtime[x] = 0;
        
        gross_pay[x] = gross_pay_calc ( hours [x], rate[x], overtime[x] ); /* Calculates gross pay */
        federal_tax [x] = tax_calc ( gross_pay[x] ); /* Calculates tax */
        net_pay[x] = net_calc ( gross_pay[x], federal_tax[x] ); /* Calculates net pay */ 
        
        total_gross = total_gross + gross_pay[x];
        total_tax = total_tax + federal_tax[x];
        total_net = total_net + net_pay[x];
        
            
        puts ( employee_name );
        printf ( "Gross Pay: $\t%.2f\n", gross_pay[x] );
        printf ( "Federal Tax: $\t%.2f\n", federal_tax[x] );
        printf ( "Net Pay: $\t%.2f\n", net_pay[x] );
        
    }
    
    printf ( "\n\n\t\tReport Totals\n" );
    printf ( "\t\t--------------\n\n");
    printf ( "Gross Pay: $\t%.2f\n", total_gross );
    printf ( "Federal Tax: $\t%.2f\n", total_tax );
    printf ( "Net Pay: $\t%.2f\n", total_net );
    
    
    
} /* End main */ 

    /* Functions below */
    /******************/
    
char get_company_name ( char name[] ) 
{   /* Prompts user for comapny name */
    printf ( "Enter the company name: ");
    safer_gets ( name, 80 );
    
    return name;
} /* End get_company_name */ 

void  safer_gets ( char array[], int max_chars ) 
{   /* Function to safely get text string input */
    int i;
 
    for (i = 0; i < max_chars; i++)
    {
        array[i] = getchar();
 
        if (array[i] == '\n')
        break;
    } 
    
    if (i == max_chars )
    if (array[i] != '\n')
    while (getchar() != '\n');
 
    array[i] = '\0';
} /* end safer_gets */

int num_of_employees ( int get_num ) 
{   /* Function to get number of employees, maximum of 10 */
    char c;
    
    do  /* Program loop to get number of employees */
    {
        
        if ( get_num < 1 || get_num > 10 ) /* Trap loop to make sure employee number is correct */
            printf ( "*** Invalid number of employees entered. Try again. ***\n\n");
    
    } while ( get_num < 1 || get_num > 10 ); 
    
    return get_num;

} /* End num_of_employees */

float overtime_calc ( float hours_worked, float pay_rate ) 
{   /* Determines amount of overtime pay earned */ 
    float overtime_pay, overtime_hours;
    
    overtime_hours = ( hours_worked - 40 ) * 1.5; /* Hours over 40 = overtime */ 
    
    overtime_pay = overtime_hours * pay_rate;
    
    return overtime_pay;
} /* End overtime_calc */

float gross_pay_calc ( float gross_hours, float gross_rate, float gross_overtime )
{   /* Determines gross pay based off of overtime + base pay */
    float gross;
    
    if ( gross_hours > 40 ) /* If hours worked is more than 40, gross pay includes overtime */
        gross = ( 40 * gross_rate ) + gross_overtime;
    else                    /* In this case there are no overtime hours to include */
        gross = ( gross_hours * gross_rate ); 
    
    return gross;
} /* End gross_pay_calc */

float tax_calc ( float pretax_pay )
{   /* Determines taxes paid for up to $999.99 and above $999.99 */
    float tax_pay;
    
    if ( pretax_pay <= 999.99 ) /* Tax rate is 20% for up to $999.99*/
        tax_pay = pretax_pay * 0.2;
    else                        /* Tax rate is 25% for pay over $999.99*/
        tax_pay = ( pretax_pay - 999.99 ) * 0.25 + ( 999.99 * 0.2 );
    
    return tax_pay;
} /* End tax_calc */

float net_calc ( float pay, float tax )
{   /* Determines after tax pay */
    float net;
    
    net = pay - tax;
    
    return net;
} /* End net_calc */
















