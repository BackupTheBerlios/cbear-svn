@echo info: %1
@cd %1
@svn --xml --recursive info > _svn.info.xml
