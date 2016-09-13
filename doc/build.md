Build lib & build sample                           {#esvg_build}
========================

@tableofcontents

Download:                                          {#esvg_build_download}
=========

esvg use some tools to manage source and build it:

lutin (build-system):                              {#esvg_build_download_lutin}
---------------------

```{.sh}
	pip install lutin --user
	# optionnal dependency of lutin (manage image changing size for application release)
	pip install pillow --user
```


dependency:                                        {#esvg_build_download_dependency}
-----------

```{.sh}
	mkdir framework
	cd framework
	git clone https://github.com/atria-soft/etk.git
	git clone https://github.com/atria-soft/exml.git
	git clone https://github.com/generic-library/gtest-lutin.git --recursive
	git clone https://github.com/generic-library/z-lutin.git --recursive
	cd ..
```

sources:                                           {#esvg_build_download_sources}
--------

```{.sh}
	cd framework
	git clone https://github.com/atria-soft/esvg.git
	cd ..
```

Build:                                             {#esvg_build_build}
======


library:                                           {#esvg_build_build_library}
--------

```{.sh}
	lutin -mdebug esvg
```

Sample:                                            {#esvg_build_build_sample}
-------

```{.sh}
	lutin -mdebug esvg-test
```


Run sample:                                        {#esvg_build_run_sample}
===========

```{.sh}
	lutin -mdebug esvg-test?run
```
