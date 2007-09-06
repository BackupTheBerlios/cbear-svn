@cd %target%
@echo info: %target%
@svn --xml --recursive info > _svn.info.xml
