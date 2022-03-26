###################################################################################
# Author		: Mahmoud Karam Emara (ma.karam272@gmail.com)
# Version		: 1.0.0
# Date 			: 26 March 2022
# Description	: makefile for automatic documentation of doxygen & Latex:	
#					<make -f doxygen.mk all>
#					* Build doxygen html files in the documentation/html directory
#					* Build PDF version in the documentation/code_documentation.pdf
###################################################################################

#---------------------------------------------------------------------------------#
# ENVIRONMENT VARIABLES: ----CHANGE THESE WHEN MOVING TO A DIFFERENT OS----		  #
#---------------------------------------------------------------------------------#
# Shell: bash for Linux, sh for MacOS, cmd for Windows
SHELL 	= cmd
# Remove files command: rm -rf for Linux, rm for MacOS, del /s /q for Windows
RM		= del /s /q
# Remove directories command: rmdir -rf for Linux or MacOS, rmdir /s /q or Windows
RMDIR 	= rmdir /s /q



#---------------------------------------------------------------------------------#
# TARGET FILES & DIRECTORIES: ----CHANGE THESE AS NEEDED----					  #
#---------------------------------------------------------------------------------#
# OUTPUT_PDF_NAME: Name of the pdf file to be generated
OUTPUT_PDF_NAME	= code_documentation
# DOC_DIR: Directory where the generated files will be moved to
DOC_DIR 		= docs
#HTML_DIR: Directory where the generated html files will be moved to
HTML_DIR		= html
#LAUNCH_DIR: Directory where the generated html files will be moved to
LATEX_DIR		= latex



#---------------------------------------------------------------------------------#
# Extra files Configurations: ----CHANGE THESE AS NEEDED----					  #
#---------------------------------------------------------------------------------#
# To not delete any of the following directories, comment it.
#TO_REMOVE_DIRS 	+= ${HTML_DIR}
TO_REMOVE_DIRS 	+= ${LATEX_DIR}



#---------------------------------------------------------------------------------#
# GENERATION OF FILES: ----DO NOT CHANGE ANYTHING BELOW THIS LINE----			  #
#---------------------------------------------------------------------------------#
# all : build all the documentation
all	: clean
	@echo Generating: html and Latex versions ...
	@doxygen
	@echo Finished generating: html and Latex versions

	@echo Generating: PDF version ...
	@${DOC_DIR}\latex\make
	@echo Finished generating: PDF version

	@echo Organising generated files in directory: ${DOC_DIR} ...
#	@-mkdir	${DOC_DIR}\${HTML_DIR} ${DOC_DIR}\${LATEX_DIR}
	@copy "${DOC_DIR}\latex\refman.pdf" "${DOC_DIR}\${OUTPUT_PDF_NAME}.pdf"
#	@xcopy ${HTML_DIR} ${DOC_DIR}\${HTML_DIR}
#	@xcopy latex ${DOC_DIR}\${LATEX_DIR}
#	${RMDIR} latex html
	cd ${DOC_DIR} && ${RMDIR} ${TO_REMOVE_DIRS}
	@echo Finished organising generated files in directory: ${DOC_DIR}

# clean : remove all generated files
clean :
	@-${RMDIR} ${DOC_DIR}\latex ${DOC_DIR}\html
	@-${RM} ${DOC_DIR}\${OUTPUT_PDF_NAME}.pdf

# Phony targets: targets that are not really files, but are used to
# control the build process. all and clean are phony targets as 
# they are not files.
.PHONY	: clean all