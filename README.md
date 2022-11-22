# INFO-H-471 Database Systems Architecure - URL Type for PostgreSQL

***

## Contents
1. [Introduction](#intro)
2. [Technologies](#technologies)
3. [Content & project structure](#content)
4. [Program usage](#usage)
5. [Contributors](#contrib)

<a name="intro"></a>

## Introduction
Within the framework of the Master's degree in Computer Science/Cybersecurity, we have been asked to create an extension for PostgreSQL allowing to support URL type. This repository contains all the source code as well as all the other informations needed in order to compile/use this extension with a PostgreSQL database.


<a name="technologies"></a>

## Technologies
To create such an extension, we have used plain C language for the functionality and created the additional functions with SQL.


<a name="content"></a>

## Content & project structure
In order to create a PostgreSQL extension, three files are essential :

- The control file which contains informations about the extension such as version, location, description, ... .
- SQL file which contains the functions definitions, casts, and more ... .
- C file containing the code which will define the behaviour of the extension. This is the core of the extension.
- Makefile to make the compilation process way easier and smoother.

Here is the structure of our project :

```bash
project
│   README.md 
└───src
    │─── url.c
    │─── url.control
    │─── url--1.0.sql
    └─── Makefile
```

<a name="usage"></a>

## Program usage
Work in progress...

<a name="contrib"></a>

## Contributors
This project has been created by 4 ULB students :

- Gullentops Charlotte (ULBId : 463980)
- ??? Julien (ULBId : )
- Botond Horac Horvath(ULBId : 440356)
- Dudziak Thomas (ULBId: 542286)




