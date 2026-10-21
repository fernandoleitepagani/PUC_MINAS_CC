# AGENTS.md

## Project

MEDIFLOW — a web system for scheduling and managing medical appointments for elderly patients, doctors, and authorized family members.

- Course: TI2 — PUC Minas, 2026/2
- Team: G4
- Stack: HTML, CSS, and JavaScript (ES modules) + JSON Server
- Application folder: `plu-cc-2026-2-ti2-4354100-plu-cc-2026-2-ti2-4354100-group-7/`

## Repository structure

```text
<repo>/
├── codigo/
│   ├── db/
│   │   └── db.json
│   └── public/
│       ├── index.html
│       ├── home.html
│       ├── about.html
│       ├── assets/
│       │   ├── css/
│       │   │   ├── style.css
│       │   │   └── <module>.css
│       │   └── js/
│       │       ├── common.js
│       │       └── <module>.js
│       └── modulos/
│           └── <module>/
│               └── index.html
├── docs/
├── .github/
│   ├── ISSUE_TEMPLATE/
│   └── PULL_REQUEST_TEMPLATE.md
├── templates/
├── README.md
├── CONTRIBUTING.md
└── package.json
```

## Mandatory rules

1. **Follow the existing structure.** Every feature goes in the same paths as the existing modules:
   - Page: `codigo/public/modulos/<module>/index.html`
   - Logic: `codigo/public/assets/js/<module>.js`
   - Styles: `codigo/public/assets/css/<module>.css`
   - Add the module link to the menu in `codigo/public/home.html`

2. **Use the shared imports.** Never duplicate helpers. Import from `codigo/public/assets/js/common.js`:
   `$`, `$$`, `buscar`, `criar`, `atualizar`, `excluir`, `porId`, `normalizar`, `formatarData`, `formatarDataHora`, `formatarHora`, `dataHoje`, `rotuloStatus`, `mostrarMensagem`, `esconderMensagem`, `criarOpcao`, `preencherSelect`, `criarLinha`.
   All page scripts must be ES modules (`<script type="module" ...>`).

3. **Use the templates.** Do not invent formats:
   - Issues: `.github/ISSUE_TEMPLATE/feature_request.md`, `bug_report.md`, `task.md`
   - Pull requests: `.github/PULL_REQUEST_TEMPLATE.md`
   - Documentation: `docs/README.md` and `templates/`
   - Git conventions: `CONTRIBUTING.md` (branch names and Conventional Commits)

4. **Reuse the UI.** Use the classes in `codigo/public/assets/css/style.css`: `.container`, `.painel`, `.campo`, `.acoes`, `.btn`, `.btn-primary`, `.btn-secondary`, `.btn-danger`, `.btn-ghost`, `.tabela`, `.linha-selecionada`, `.filtros`, `.alerta-*`, `.mensagem-vazia`.
   The module CSS should only add layout rules that `style.css` does not cover.
   The visual style must follow the wireframes and interface documents in `docs/` and/or the `cadastro-pacientes` page (`codigo/public/modulos/pacientes/index.html`), including its layout and colors. Use the `--mf-*` variables from `style.css`; do not introduce a new visual language or palette.

5. **Keep the code simple.** Prefer the smallest working change. No new frameworks, libraries, or dependencies unless strictly necessary. No over-engineering, no unused abstractions, no speculative features.

6. **Use the existing data model.** Work with the collections and field names already present in `codigo/db/db.json`. Compare IDs safely with `String(id)`, since some collections use string IDs.

7. **Match the code style.** 2-space indentation, double quotes, semicolons, `const`/`let`, DOM creation via `document.createElement` and `textContent` for user data (avoid `innerHTML`). UI text, messages, and documentation in Portuguese; follow the existing identifier names in Portuguese.

8. **Comments must be minimal, concise, and objective.** Only explain non-obvious decisions. Do not restate what the code already says. Follow the existing codebase, which keeps comments rare.

## Git — hard rule

**LLMs must never run `git commit`, `git push`, `gh pr create`, `gh issue create`, or any command that writes to the repository history or to GitHub on their own.**

Make the file changes and provide the exact commands for the user to run.

Additional git rules:

- Never commit directly to `master` or `docs`.
- Use a temporary branch: `feat/`, `fix/`, `docs/`, `refactor/`, `test/`, `chore/`, or `style/`.
- Follow Conventional Commits: `type(scope): description`.

## Running locally

```bash
npm install
npm run api    # JSON Server on port 3001
npm run front  # frontend on port 3000
```

If `npm start` or `npm run dev` exist in `package.json`, they may be used instead.
