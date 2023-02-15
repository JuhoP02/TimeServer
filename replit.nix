{ pkgs }: {
	deps = [
		pkgs../server
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}