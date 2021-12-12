<script lang="ts">
	import { minimum2IntegerDigits } from '$lib/utilities';

	let irrigationEndTime: number = 0;
	let Irrigating = false;
	let countDownText: string = '';

	async function irrigate() {
		const response = await fetch('/irrigate');
		Irrigating = true;

		const irrigationJson = await response.json();

		irrigationEndTime = irrigationJson.irrigationEndTime * 1000;

		const irrigationIterval = setInterval(() => {
			const rigthNow = Date.now();

			const countDown = irrigationEndTime - rigthNow;

			const date = new Date(countDown);

			const seconds = minimum2IntegerDigits(date.getSeconds());
			const minutes = minimum2IntegerDigits(date.getMinutes());

			countDownText = `Irrigando: ${minutes}:${seconds}`;

			if (countDown <= 0) {
				Irrigating = false;
				clearInterval(irrigationIterval);
			}
		}, 100);
	}

	async function stopIrrigation() {
		const response = await fetch('/stopIrrigation');
		if (response.ok) {
			irrigationEndTime = Date.now();
		}
	}
</script>

<div>
	<p>
		{#if Irrigating}
			{countDownText}
		{/if}
	</p>

	<button on:click={irrigate} class="irrigate" disabled={Irrigating}>Irrigar</button>
	<button on:click={stopIrrigation} class="stopIrrigation">Parar Irrigação</button>
</div>

<style>
	button {
		height: 32px;
		width: 112px;
		border-radius: 4px;
	}
	button:active {
		color: var(--primary-color-1);
		background: #d8e9a8;
		border: inset 2px #d8e9a8;
	}
	button:disabled {
		background: var(--secondary-color);
		color: var(--text-color);
		border: solid 2px var(--secondary-color);
	}

	div {
		display: grid;
		gap: 4px;
		grid-template-rows: 24px auto;
		grid-template-columns: 1fr 1fr;
		width: 100%;
	}

	p {
		font-size: 1em;
		align-items: center;
		text-align: center;
		align-self: center;
		justify-self: center;
		grid-column-start: 1;
		grid-column-end: 3;
	}

	.irrigate {
		background: var(--accent-color);
		border: outset 2px var(--accent-color);
		justify-self: end;
	}

	.stopIrrigation {
		background: #ff5a5c;
		border: outset 2px #ff5a5c;
		justify-self: start;
	}
</style>
