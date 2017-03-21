all:
	$(MAKE) -C libqap
	$(MAKE) -C tools/qapcombine
	$(MAKE) -C tools/qapcombine_stat
	$(MAKE) -C tools/qapgenf
	$(MAKE) -C tools/qapinput_surv
	$(MAKE) -C tools/qapprove_anon
	$(MAKE) -C tools/qapver
	$(MAKE) -C tools/qapver_stat
	$(MAKE) -C tools/qapcombine_anon
	$(MAKE) -C tools/qapgen
	$(MAKE) -C tools/qapinput
	$(MAKE) -C tools/qapprove
	$(MAKE) -C tools/qapprove_stat
	$(MAKE) -C tools/qapver_anon
	cp tools/qapcombine/qapcombine bin/
	cp tools/qapcombine_stat/qapcombine_stat bin/
	cp tools/qapgenf/qapgenf bin/
	cp tools/qapinput_surv/qapinput_surv bin/
	cp tools/qapprove_anon/qapprove_anon bin/
	cp tools/qapver/qapver bin/
	cp tools/qapver_stat/qapver_stat  bin/
	cp tools/qapcombine_anon/qapcombine_anon bin/
	cp tools/qapgen/qapgen bin/
	cp tools/qapinput/qapinput bin/
	cp tools/qapprove/qapprove bin/
	cp tools/qapprove_stat/qapprove_stat bin/
	cp tools/qapver_anon/qapver_anon bin/
